
#include "ParserPacketMySQL.h"
#include "../core/utils.h"

std::string readStringNULL(std::string payload, size_t offset)
{
	size_t nulpos = payload.find('\000', offset);
	if (nulpos == std::string::npos) {
		return ("");
	} else {
		std::string r = payload.substr(offset, nulpos-offset);
		return (r);
	}
}

unsigned long long readLenEnc(std::string payload, size_t offset)
{
	unsigned long long r = 0;
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
		r += (unsigned long long)payload[offset+1] << 56;
		r += (unsigned long long)payload[offset+2] << 48;
		r += (unsigned long long)payload[offset+3] << 40;
		r += (unsigned long long)payload[offset+4] << 32;
		r += (unsigned long long)payload[offset+5] << 24;
		r += (unsigned long long)payload[offset+6] << 16;
		r += (unsigned long long)payload[offset+7] << 8;
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
		return (4);
	}
	return (9);
}

uint32_t ParserPacketMySQL::GetPayloadLength(std::shared_ptr<EndPoint> flow)
{
	std::string preview = flow->GetPayloadPreview();
	uint32_t length = ((unsigned char)preview[2] << 16) | ((unsigned char)preview[1] << 8) | (unsigned char)preview[0];

	return (length);
}

std::string ParserPacketMySQL::ReadPacketPreview(uint32_t length, std::shared_ptr<EndPoint> flow)
{
	try {
		uint32_t readBytes = std::min(length, (uint32_t)200);
		std::string r = flow->Payload->GetSubStringOrFail(4, readBytes);
//		std::cout << "length " << length
//				<< ", s_port=" << flow->LastChunk->SourcePort
//				<< ", d_port=" << flow->LastChunk->DestinationPort
//				<< ", protocol=" << int(r[0])
//				<< "\n";
		return (r);
	} catch (...) {
		return ("");
	}
}

bool isPrintable(std::string &str) {
	for(size_t i=0; i<str.size(); i++) {
		if (str[i] < 32 || str[i] > 127)
			return (false);
	}

	return (true);
}

std::shared_ptr<PacketMySQL> ParserPacketMySQL::DefaultCase(
		std::shared_ptr<SessionTCP> session
		, uint32_t packetLength)
{
	if (session->ProtocolDetected) {
		return (std::make_shared<PacketMySQL>(session->BaseData
				, session->Payload
				, session
				, nullptr
				, nullptr
				, packetLength));
	} else {
		return (std::shared_ptr<PacketMySQL>(nullptr));
	}
}

std::shared_ptr<PacketMySQL> ParserPacketMySQL::ParseHandshakeResponse(
		std::shared_ptr<SessionTCP> session
		, std::string payload
		, uint32_t packetLength)
{
	size_t offset = 0;

	uint32_t capFlags =
			((uint32_t)payload[offset] << 24)
			+ ((uint32_t)payload[offset+1] << 16)
			+ ((uint32_t)payload[offset+2] << 8)
			+ payload[offset+3];
	offset+=4;

	if (capFlags & 0x00000200) {
		uint32_t maxPktLen =
				((uint32_t)payload[offset] << 24)
				+ ((uint32_t)payload[offset+1] << 16)
				+ ((uint32_t)payload[offset+2] << 8)
				+ payload[offset+3];
		offset+=4;

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

		std::unique_ptr<MySQLRequest> req(new MySQLRequest(0));

		PacketMySQL *r = new PacketMySQL(session->BaseData
				, session->Payload
				, session
				, std::move(req)
				, nullptr
				, packetLength);
		r->Username = username;
		r->Database = database;
		r->Charset = charset;
		r->MaxPktLen = maxPktLen;

		session->ProtocolDetected = true;
		session->Follower = this->AsFollower();

		std::cout << "user=" << username << "\n";

		return (std::shared_ptr<PacketMySQL>(r));
	}
	return (std::shared_ptr<PacketMySQL>(nullptr));
}

std::shared_ptr<PacketMySQL> ParserPacketMySQL::ParseCommand(
		std::shared_ptr<SessionTCP> session
		, std::string payload
		, uint32_t packetLength)
{
	char cmd = payload[0];
	if (cmd == 0x02) {
		// COM_INIT_DB
		std::string new_db = payload.substr(1, payload.length()-1);
		if (!isPrintable(new_db) || new_db.empty())
			return (std::shared_ptr<PacketMySQL>(nullptr));

		std::unique_ptr<MySQLRequest> req(new MySQLRequest(cmd));
		PacketMySQL *r = new PacketMySQL(session->BaseData
				, session->Payload
				, session
				, std::move(req)
				, nullptr
				, packetLength);
		return (std::shared_ptr<PacketMySQL>(r));
	} else if (cmd == 0x03) {
		std::string query = payload.substr(1, payload.length()-1);

		pcrecpp::StringPiece input(query);

		std::string queryType;
		if (QueryCheckRe.PartialMatch(input, &queryType)) {
			std::unique_ptr<MySQLRequest> req(new MySQLRequest(cmd));
			req->Query = query;
			req->QueryType = util::toLower(queryType);
			std::cout << "queryType " << req->QueryType << "\n";

			PacketMySQL *r = new PacketMySQL(session->BaseData
					, session->Payload
					, session
					, std::move(req)
					, nullptr
					, packetLength);

			session->ProtocolDetected = true;
			session->Follower = this->AsFollower();

			return (std::shared_ptr<PacketMySQL>(r));
		}
	}
	return (DefaultCase(session, packetLength));
}

std::shared_ptr<PacketMySQL> ParserPacketMySQL::ParseClient(
		std::shared_ptr<SessionTCP> session
		, std::shared_ptr<EndPoint> flow)
{
	if (flow->Payload.get() != nullptr && flow->Payload->CoveredSize) {
		try {
			uint32_t pktLen = GetPayloadLength(flow);
			try {
				std::string payload = ReadPacketPreview(pktLen, flow);
				if (!payload.empty()) {
					std::shared_ptr<PacketMySQL> r;

					r = ParseHandshakeResponse(session, payload, pktLen);
					if (r != nullptr)
						return (r);

					r = ParseCommand(session, payload, pktLen);
				}
			} catch (...) {
			}
			return (DefaultCase(session, pktLen));
		} catch (...) {
		}
	}
	return (DefaultCase(session, 0));
}

std::shared_ptr<PacketMySQL> ParserPacketMySQL::ParseServer(
		std::shared_ptr<SessionTCP> session
		, std::shared_ptr<EndPoint> flow)
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
						unsigned long connectionId =
								((int)payload[offset] << 24)
								+ ((int)payload[offset+1] << 16)
								+ ((int)payload[offset+2] << 8)
								+ payload[offset+3];
						offset+=4;

						std::string auth_plugin_data_part_1 = payload.substr(offset, 8);
						offset+=8;

						if (payload[offset] != 0)
							return (std::shared_ptr<PacketMySQL>(nullptr));
						offset++;

						int capFlags =
								((int)payload[offset] << 8)
								+ payload[offset+1];
						offset+=2;

						size_t auth_plugin_data_length = payload[offset];
						offset++;

						if (((capFlags & 0x00080000) && auth_plugin_data_length == 0)
								|| (!(capFlags & 0x00080000) && payload[offset] != 0))
							return (std::shared_ptr<PacketMySQL>(nullptr));

						std::unique_ptr<MySQLResponse> req(new MySQLResponse);

						PacketMySQL *r = new PacketMySQL(session->BaseData
								, session->Payload
								, session
								, nullptr
								, std::move(req)
						, pktLen);
						r->ServerVersion = serverVersion;
						r->ConnectionID = connectionId;

						session->ProtocolDetected = true;
						session->Follower = this->AsFollower();

						return (std::shared_ptr<PacketMySQL>(r));
					}
				}
			} catch (...) {
			}
			return (DefaultCase(session, pktLen));
		} catch (...) {
		}
	}
	return (DefaultCase(session, 0));
}

std::shared_ptr<PacketMySQL> ParserPacketMySQL::Process(std::shared_ptr<SessionTCP> session)
{
	std::shared_ptr<PacketMySQL> r = ParseClient(session, session->Client);
	if (r != nullptr)
		return (r);

	r = ParseServer(session, session->Client);
	if (r != nullptr) {
		session->SwapFlows();
		return (r);
	}

	r = ParseClient(session, session->Server);
	if (r != nullptr) {
		session->SwapFlows();
		return (r);
	}

	r = ParseServer(session, session->Server);
	return (r);
}

ParserPacketMySQL::ParserPacketMySQL()
	: QueryCheckRe("^(select|update|delete|insert|show|set)\\s+", pcrecpp::RE_Options().set_caseless(true))
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
