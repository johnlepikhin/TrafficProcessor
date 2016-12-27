// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "ParserPacketMySQL.h"
#include "../core/utils.h"

std::string readStringNULL(const std::string &payload, size_t offset)
{
	size_t nulpos = payload.find('\000', offset);
	if (nulpos == std::string::npos) {
		return ("");
	} else {
		std::string r = payload.substr(offset, nulpos-offset);
		return (r);
	}
}

uint64_t readLenEnc(const std::string &payload, size_t offset)
{
	uint64_t r = 0;
	if (payload[offset] < 0xfb) {
		r = payload[offset];
	} else if (payload[offset] == 0xfc) {
		r += payload[offset+1] << 8;
		r += payload[offset+2];
	} else if (payload[offset] == 0xfd) {
		r += payload[offset+1] << 16;
		r += payload[offset+2] << 8;
		r += payload[offset+3];
	} else if (payload[offset] == 0xfe) {
		r += static_cast<uint64_t>(payload[offset+1]) << 56;
		r += static_cast<uint64_t>(payload[offset+2]) << 48;
		r += static_cast<uint64_t>(payload[offset+3]) << 40;
		r += static_cast<uint64_t>(payload[offset+4]) << 32; //-V112
		r += static_cast<uint64_t>(payload[offset+5]) << 24;
		r += static_cast<uint64_t>(payload[offset+6]) << 16;
		r += static_cast<uint64_t>(payload[offset+7]) << 8;
		r += payload[offset+8];
	}
	return (r);
}

size_t lengthLenEnc(unsigned long long v) {
	if (v < 251) {
		return (2);
	} else if (v < 0x10000) {
		return (3);
	} else if (v < 0x1000000) {
		return (4); //-V112
	}
	return (9);
}

uint32_t ParserPacketMySQL::GetPayloadLength(const std::shared_ptr<EndPoint> &flow)
{
	std::string *preview = flow->GetPayloadPreview();
	uint32_t length =
			(static_cast<unsigned char>(preview->at(2)) << 16)
			| (static_cast<unsigned char>(preview->at(1)) << 8)
			| static_cast<unsigned char>(preview->at(0));

	return (length);
}

std::string ParserPacketMySQL::ReadPacketPreview(uint32_t length, const std::shared_ptr<EndPoint> &flow)
{
	try {
		std::string *buf = flow->GetPayloadPreview();
		uint32_t readBytes = std::min(length, static_cast<uint32_t>(buf->length()-4)); //-V112
		std::string r(buf->substr(4, readBytes)); //-V112
		return (r);
	} catch (...) {
		return ("");
	}
}

bool isPrintable(const std::string &str) {
	for(size_t i=0; i<str.size(); i++) {
		if (str[i] < 32 || str[i] > 127) //-V112
			return (false);
	}

	return (true);
}

std::shared_ptr<PacketMySQL> ParserPacketMySQL::DefaultCase(
		const std::shared_ptr<SessionTCP> &session
		, std::shared_ptr<PacketMySQL> chunk
		, uint32_t packetLength)
{
	if (session->Follower != nullptr) {
		chunk->PacketLength = packetLength;
		return (chunk);
	} else {
		return (std::shared_ptr<PacketMySQL>(nullptr));
	}
}

std::shared_ptr<PacketMySQL> ParserPacketMySQL::ParseHandshakeResponse(
		const std::shared_ptr<SessionTCP> &session
		, std::shared_ptr<PacketMySQL> chunk
		, const std::string &payload
		, uint32_t packetLength)
{
	size_t offset = 0;

	uint32_t capFlags =
			(static_cast<uint32_t>(payload[offset]) << 24)
			+ (static_cast<uint32_t>(payload[offset+1]) << 16)
			+ (static_cast<uint32_t>(payload[offset+2]) << 8)
			+ payload[offset+3];
	offset+=4; //-V112

	if (capFlags & 0x00000200) {
		uint32_t maxPktLen =
				(static_cast<uint32_t>(payload[offset]) << 24)
				+ (static_cast<uint32_t>(payload[offset+1]) << 16)
				+ (static_cast<uint32_t>(payload[offset+2]) << 8)
				+ payload[offset+3];
		offset+=4; //-V112

		int charset = payload[0];
		offset++;

		std::string reserved = payload.substr(offset, 23);
		offset+=23;

		for (size_t i=0; i<reserved.size(); i++) {
			if (reserved[i] != '\000') {
				return (std::shared_ptr<PacketMySQL>(nullptr));
			}
		}

		std::string username = readStringNULL(payload, offset);
		if (!isPrintable(username) || username.empty())
			return (std::shared_ptr<PacketMySQL>(nullptr));
		offset += username.length() + 1;

		std::string auth_response("");
		if (capFlags & 0x00200000) {
			unsigned long long auth_response_length = readLenEnc(payload, offset);
			offset += lengthLenEnc(auth_response_length);
			auth_response = payload.substr(offset, auth_response_length);
			offset += auth_response_length;
		} else if (capFlags & 0x00008000) {
			size_t auth_response_length = payload[offset];
			offset++;
			auth_response = payload.substr(offset, auth_response_length);
			offset += auth_response_length;
		} else {
			auth_response = readStringNULL(payload, offset);
			offset += auth_response.size()+1;
		}

		std::string database("");
		if (capFlags & 0x00000008) {
			database = readStringNULL(payload, offset);
			offset += database.size()+1;

			if (!isPrintable(database))
				return (std::shared_ptr<PacketMySQL>(nullptr));
		}

		chunk->Request.reset(new MySQLRequest(0));
		chunk->Username = username;
		chunk->Database = database;
		chunk->Charset = charset;
		chunk->MaxPktLen = maxPktLen;

		return (chunk);
	}
	return (std::shared_ptr<PacketMySQL>(nullptr));
}

std::shared_ptr<PacketMySQL> ParserPacketMySQL::ParseCommand(
		const std::shared_ptr<SessionTCP> &session
		, std::shared_ptr<PacketMySQL> chunk
		, const std::string &payload
		, uint32_t packetLength)
{
	if (session->Follower == nullptr)
		return (std::shared_ptr<PacketMySQL>(nullptr));

	char cmd = payload[0];
	if (cmd == 0x02) {
		// COM_INIT_DB
		std::string new_db = payload.substr(1, payload.length()-1);
		if (!isPrintable(new_db) || new_db.empty())
			return (std::shared_ptr<PacketMySQL>(nullptr));

		chunk->Request.reset(new MySQLRequest(cmd));
		chunk->PacketLength = packetLength;
		return (chunk);
	} else if (cmd == 0x03) {
		std::string query = payload.substr(1, payload.length()-1);

		pcrecpp::StringPiece input(query);

		std::string queryType;
		if (QueryCheckRe.PartialMatch(input, &queryType)) {
			chunk->Request.reset(new MySQLRequest(cmd));
			chunk->Request->Query = query;
			chunk->Request->QueryType = util::toLower(queryType);
			chunk->PacketLength = packetLength;

			return (chunk);
		}
	}
	return (DefaultCase(session, chunk, packetLength));
}

std::shared_ptr<PacketMySQL> ParserPacketMySQL::ParseClient(
		const std::shared_ptr<SessionTCP> &session
		, const std::shared_ptr<PacketMySQL> chunk
		, const std::shared_ptr<EndPoint> &flow)
{
	if (flow->Payload.get() != nullptr && flow->Payload->CoveredSize) {
		try {
			uint32_t pktLen = GetPayloadLength(flow);
			try {
				std::string payload = ReadPacketPreview(pktLen, flow);
				if (!payload.empty()) {
					std::shared_ptr<PacketMySQL> r = ParseHandshakeResponse(session, chunk, payload, pktLen);

					if (r != nullptr) {
						return (r);
					}

					return (ParseCommand(session, chunk, payload, pktLen));
				}
			} catch (...) {
				return (DefaultCase(session, chunk, pktLen));
			}
			return (DefaultCase(session, chunk, pktLen));
		} catch (...) {
			return (DefaultCase(session, chunk, 0));
		}
	}
	return (DefaultCase(session, chunk, 0));
}

std::shared_ptr<PacketMySQL> ParserPacketMySQL::ParseServer(
		const std::shared_ptr<SessionTCP> &session
		, std::shared_ptr<PacketMySQL> chunk
		, const std::shared_ptr<EndPoint> &flow)
{
	if (flow->Payload.get() != nullptr && flow->Payload->CoveredSize) {
		try {
			uint32_t pktLen = GetPayloadLength(flow);
			try {
				std::string payload = ReadPacketPreview(pktLen, flow);
				if (!payload.empty()) {
					if (payload[0] == 10) {
						std::string serverVersion = readStringNULL(payload, 1);
						if (serverVersion.empty())
							return (std::shared_ptr<PacketMySQL>(nullptr));

						if (!isPrintable(serverVersion))
							return (std::shared_ptr<PacketMySQL>(nullptr));

						size_t offset = 1 + serverVersion.size() + 1;
						uint32_t connectionId =
								(static_cast<int>(payload[offset]) << 24)
								+ (static_cast<int>(payload[offset+1]) << 16)
								+ (static_cast<int>(payload[offset+2]) << 8)
								+ payload[offset+3];
						offset+=4; //-V112

						//						std::string auth_plugin_data_part_1 = payload.substr(offset, 8);
						offset+=8;

						if (payload[offset] != 0)
							return (std::shared_ptr<PacketMySQL>(nullptr));
						offset++;

						uint16_t capFlags =
								(static_cast<uint16_t>(payload[offset]) << 8)
								+ payload[offset+1];
						offset+=2;

						size_t auth_plugin_data_length = payload[offset];
						offset++;

						if (((capFlags & 0x00080000) && auth_plugin_data_length == 0)
								|| (!(capFlags & 0x00080000) && payload[offset] != 0))
							return (std::shared_ptr<PacketMySQL>(nullptr));

						chunk->Response = std::unique_ptr<MySQLResponse>(new MySQLResponse(MySQL_AUTH));
						chunk->PacketLength = pktLen;
						chunk->ServerVersion = serverVersion;
						chunk->ConnectionID = connectionId;

						return (chunk);
					} else if (session->Follower != nullptr) {
						if (payload[0] == 0x00 || payload[0] == 0xfe) {
							std::unique_ptr<MySQLResponse> resp(new MySQLResponse(MySQL_OK));

							uint32_t offset = 1;

							resp->AffectedRows = readLenEnc(payload, offset);
							offset += lengthLenEnc(resp->AffectedRows);

							resp->LastInsertID = readLenEnc(payload, offset);
							offset += lengthLenEnc(resp->LastInsertID);

							resp->StatusFlags = (payload[offset] << 8) + (payload[offset+1]);

							chunk->Response = std::move(resp);
							chunk->PacketLength = pktLen;

							return (chunk);
						} else if (payload[0] == 0xff) {
							std::unique_ptr<MySQLResponse> resp(new MySQLResponse(MySQL_ERROR));

							uint32_t offset = 1;
							resp->ErrorCode = (payload[offset] << 8) + (payload[offset+1]);

							chunk->Response = std::move(resp);
							chunk->PacketLength = pktLen;

							return (chunk);
						}
					}

				}
			} catch (...) {
				return (DefaultCase(session, chunk, pktLen));
			}
			return (DefaultCase(session, chunk, pktLen));
		} catch (...) {
			return (DefaultCase(session, chunk, 0));
		}
	}
	return (DefaultCase(session, chunk, 0));
}

std::shared_ptr<PacketMySQL> ParserPacketMySQL::FollowerProcess(const std::shared_ptr<SessionTCP> &session, std::shared_ptr<PacketMySQL> follower)
{
	std::shared_ptr<PacketMySQL> chunk = (follower != nullptr)
		? follower
		: std::make_shared<PacketMySQL>(session->BaseData, session->Payload, session, nullptr, nullptr, 0);

	std::shared_ptr<PacketMySQL> r = ParseClient(session, chunk, session->Client);
	if (r != nullptr)
		return (r);

	r = ParseServer(session, chunk, session->Client);
	if (r != nullptr) {
		session->SwapFlows();
		return (r);
	}

	r = ParseClient(session, chunk, session->Server);
	if (r != nullptr) {
		session->SwapFlows();
		return (r);
	}

	r = ParseServer(session, chunk, session->Server);
	return (r);

}

ParserPacketMySQL::ParserPacketMySQL()
	: TCPSessionFollowerHolder<PacketMySQL>()
	, QueryCheckRe("^(select|update|delete|insert|show|set)\\s+", pcrecpp::RE_Options().set_caseless(true))
{
}

/**
 * Returns unique ID for this Parser
 * @return ID
 */
std::string ParserPacketMySQL::ID()
{
	return ("MySQL");
}

/**
 * Returns description for this Parser
 * @return Description
 */
std::string ParserPacketMySQL::Description()
{
	return ("MySQL parser");
}
