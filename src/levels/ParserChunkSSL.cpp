// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "ParserChunkSSL.h"
#include <exception>

SSLRecordType RecordTypeOfByte(const uint8_t &byte) {
	switch (byte) {
	case 0x14: return (CHANGE_CIPHER_SPEC);
	case 0x15: return (ALERT);
	case 0x16: return (HANDSHAKE);
	case 0x17: return (APPLICATION_DATA);
	}

	throw std::invalid_argument("byte");
}

SSLAlertSeverity AlertSeverityOfByte(const uint8_t &byte) {
	switch (byte) {
	case 0x01: return(WARNING);
	case 0x02: return(FATAL);
	}

	throw std::invalid_argument("byte");
}

SSLAlertDescription AlertDescriptionOfByte(const uint8_t &byte) {
	switch (byte) {
	case 0x00: return(CLOSE_NOTIFY);
	case 0x0A: return(UNEXPECTED_MESSAGE);
	case 0x14: return(BAD_RECORD_MAC);
	case 0x15: return(DECRYPTION_FAILED);
	case 0x16: return(RECORD_OVERFLOW);
	case 0x1E: return(DECOMPRESSION_FAILURE);
	case 0x28: return(HANDSHAKE_FAILURE);
	case 0x29: return(NO_CERTIFICATE);
	case 0x2A: return(BAD_CERTIFICATE);
	case 0x2B: return(UNSUPPORTED_CERTIFICATE);
	case 0x2C: return(CERTIFICATE_REVOKED);
	case 0x2D: return(CERTIFICATE_EXPIRED);
	case 0x2E: return(CERTIFICATE_UNKNOWN);
	case 0x2F: return(ILLEGAL_PARAMETER);
	case 0x30: return(UNKNOWN_CA);
	case 0x31: return(ACCESS_DENIED);
	case 0x32: return(DECODE_ERROR);
	case 0x33: return(DECRYPT_ERROR);
	case 0x3C: return(EXPORT_RESTRICTION);
	case 0x46: return(PROTOCOL_VERSION);
	case 0x47: return(INSUFFICIENT_SECURITY);
	case 0x50: return(INTERNAL_ERROR);
	case 0x5A: return(USER_CANCELLED);
	case 0x64: return(NO_RENEGOTIATION);
	}

	throw std::invalid_argument("byte");
}

std::unique_ptr<SSLAlert> ParserChunkSSL::AlertParser(const std::shared_ptr<SessionTCP> &session
		, const std::shared_ptr<EndPoint> &flow
		, const std::string *preview)
{
	try {
		SSLAlertSeverity severity = AlertSeverityOfByte(preview->at(5));
		SSLAlertDescription description = AlertDescriptionOfByte(preview->at(6));
		return (std::unique_ptr<SSLAlert>(new SSLAlert(severity, description)));
	} catch (...) {
		return (std::unique_ptr<SSLAlert>(nullptr));
	}
}

SSLHandshakeType HandshakeTypeOfByte(const uint8_t &byte) {
	switch (byte) {
	case 0x00: return(HELLO_REQUEST);
	case 0x01: return(CLIENT_HELLO);
	case 0x02: return(SERVER_HELLO);
	case 0x0b: return(CERTIFICATE);
	case 0x0c: return(SERVER_KEY_EXCHANGE);
	case 0x0d: return(CERTIFICATE_REQUEST);
	case 0x0e: return(SERVER_DONE);
	case 0x0f: return(CERTIFICATE_VERIFY);
	case 0x10: return(CLIENT_KEY_EXCHANGE);
	case 0x14: return(FINISHED);
	}

	throw std::invalid_argument("byte");
}

void UpdateFlowDirection(const std::shared_ptr<SessionTCP> &session
		, const std::shared_ptr<EndPoint> &flow
		, SSLHandshakeType type)
{
	bool isClient = flow == session->Client;

	if (isClient && (type == HELLO_REQUEST
			|| type == SERVER_HELLO
			|| type == SERVER_KEY_EXCHANGE
			|| type == CERTIFICATE_REQUEST
			|| type == SERVER_DONE
			|| type == FINISHED)) {
		session->SwapFlows();
		return;
	}

	if (!isClient && (type == CLIENT_HELLO
			|| type == CLIENT_KEY_EXCHANGE
			|| type == CERTIFICATE_VERIFY)) {
		session->SwapFlows();
		return;
	}
}

std::unique_ptr<SSLCertificate> ParserChunkSSL::CertificateParser(const std::string *preview)
{
	try {
		uint32_t chainLength = (preview->at(9) << 16)
					+ (preview->at(10) << 8)
					+ preview->at(11);

		uint32_t processed = 0;
		std::vector<std::string> certificates;
		uint32_t offset = 12;

		uint32_t previewLength = preview->length();

		while (processed < chainLength) {
			if (offset + 3 < previewLength)
				break;

			uint32_t certificateLength = (preview->at(offset) << 16)
							+ (preview->at(offset+1) << 8)
							+ preview->at(offset+2);
			offset+=3;

			if (offset + certificateLength < previewLength)
				break;

			std::string certificate(preview->substr(offset, certificateLength));
			certificates.push_back(certificate);
			offset+=certificateLength;
		}
		return (std::unique_ptr<SSLCertificate>(new SSLCertificate(certificates)));
	} catch (...) {
		return (std::unique_ptr<SSLCertificate>(nullptr));
	}
}

std::unique_ptr<SSLHello> ParserChunkSSL::HelloParser(const std::string *preview)
{
	uint16_t version = (preview->at(9) << 8) + (preview->at(10));
	if ((version < 0x300) || (version > 0x303))
		return (std::unique_ptr<SSLHello>(nullptr));

	uint32_t random = (preview->at(11) << 24)
			+ (preview->at(12) << 16)
			+ (preview->at(13) << 8)
			+ preview->at(14);

	uint8_t sessionIDLength = preview->at(15);

	uint32_t sessionID = 0;
	switch (sessionIDLength) {
	case 0:
		break;
	case 1:
		sessionID = preview->at(16);
		break;
	case 2:
		sessionID = (preview->at(16) << 8)
			+ preview->at(17);
		break;
	case 3:
		sessionID = (preview->at(16) << 16)
			+ (preview->at(17) << 8)
			+ preview->at(18);
		break;
	case 4:
		sessionID = (preview->at(16) << 24)
			+ (preview->at(17) << 16)
			+ (preview->at(18) << 8)
			+ preview->at(19);
		break;
	default:
		return (std::unique_ptr<SSLHello>(nullptr));
	}

	return (std::unique_ptr<SSLHello>(new SSLHello(version, random, sessionIDLength, sessionID)));
}

std::unique_ptr<SSLHandshake> ParserChunkSSL::HandshakeParser(const std::shared_ptr<SessionTCP> &session
		, const std::shared_ptr<EndPoint> &flow
		, const std::string *preview
		, const uint16_t recordLength)
{
	try {
		SSLHandshakeType type = HandshakeTypeOfByte(preview->at(5));

		uint32_t length = (preview->at(6) << 16)
				+ (preview->at(7) << 8)
				+ preview->at(8);

		switch (type) {
		case CLIENT_HELLO:
		case SERVER_HELLO: {
			if (recordLength < 11 || preview->length() < 16)
				return (std::unique_ptr<SSLHandshake>(nullptr));
			std::unique_ptr<SSLHello> hello = HelloParser(preview);
			if (hello != nullptr) {
				UpdateFlowDirection(session, flow, type);
				return (std::unique_ptr<SSLHandshake>(new SSLHandshake(type, length, std::move(hello), nullptr)));
			}
			break;
		}
		case CERTIFICATE: {
			if (recordLength < 7 || preview->length() < 12)
				return (std::unique_ptr<SSLHandshake>(nullptr));
			std::unique_ptr<SSLCertificate> certificate = CertificateParser(preview);
			if (certificate != nullptr) {
				UpdateFlowDirection(session, flow, type);
				return (std::unique_ptr<SSLHandshake>(new SSLHandshake(type, length, nullptr, std::move(certificate))));
			}
			break;
		}

		default:
			UpdateFlowDirection(session, flow, type);
			return (std::unique_ptr<SSLHandshake>(new SSLHandshake(type, length, nullptr, nullptr)));
			break;
		}
	} catch (...) {
		return (std::unique_ptr<SSLHandshake>(nullptr));
	}


	return (std::unique_ptr<SSLHandshake>(nullptr));
}


std::shared_ptr<ChunkSSL> ParserChunkSSL::FlowParser(const std::shared_ptr<SessionTCP> &session
		, const std::shared_ptr<EndPoint> &flow)
{
	try {
		if (flow->Payload.get() != nullptr && flow->Payload->CoveredSize) {
			std::string *preview = flow->GetPayloadPreview();
			if (preview->length() >= 5) {
				try {
					SSLRecordType recordType = RecordTypeOfByte(preview->at(0));
					uint16_t version = (preview->at(1) << 8) + (preview->at(2));
					uint16_t length = (preview->at(3) << 8) + (preview->at(4)); //-V112

					if ((version < 0x300) || (version > 0x303) || (length > 16384))
						return (std::shared_ptr<ChunkSSL>(nullptr));

					switch (recordType) {
						case CHANGE_CIPHER_SPEC: {
							if (length != 1 || preview->at(5) != 1)
								return (std::shared_ptr<ChunkSSL>(nullptr));
							std::cout << "CHANGE_CIPHER_SPEC\n";
							return (std::make_shared<ChunkSSL>(session, CHANGE_CIPHER_SPEC, version, length, nullptr, nullptr));
						}

						case ALERT: {
							std::unique_ptr<SSLAlert> alert = AlertParser(session, flow, preview);
							if (alert != nullptr && length == 2) {
								session->Follower = this->AsFollower();
								return (std::make_shared<ChunkSSL>(session, ALERT, version, length, std::move(alert), nullptr));
							}
							return (std::shared_ptr<ChunkSSL>(nullptr));
						}

						case (HANDSHAKE): {
							std::unique_ptr<SSLHandshake> handshake = HandshakeParser(session, flow, preview, length);
							if (handshake != nullptr) {
								session->Follower = this->AsFollower();
								return (std::make_shared<ChunkSSL>(session, HANDSHAKE, version, length, nullptr, std::move(handshake)));
							}
							return (std::shared_ptr<ChunkSSL>(nullptr));
						}

						case APPLICATION_DATA: {
							session->Follower = this->AsFollower();
							return (std::make_shared<ChunkSSL>(session, APPLICATION_DATA, version, length, nullptr, nullptr));
						}
					}

				} catch (...) {
					return (std::shared_ptr<ChunkSSL>(nullptr));
				}
			}
		}
	} catch (...) {
		return (std::shared_ptr<ChunkSSL>(nullptr));
	}
	return (std::shared_ptr<ChunkSSL>(nullptr));
}

std::shared_ptr<ChunkSSL> ParserChunkSSL::Process(const std::shared_ptr<SessionTCP> &session)
{
	std::shared_ptr<ChunkSSL> r = FlowParser(session, session->Client);
	if (r != nullptr)
		return (r);

	r = FlowParser(session, session->Server);
	if (r != nullptr)
		return (r);

	if (session->Follower != nullptr)
		return (std::make_shared<ChunkSSL>(session, APPLICATION_DATA, 0, 0, nullptr, nullptr));

	return (std::shared_ptr<ChunkSSL>(nullptr));
}


/**
 * Returns unique ID for this Parser
 * @return ID
 */
std::string ParserChunkSSL::ID()
{
	return ("SSL");
}

/**
 * Returns description for this Parser
 * @return Description
 */
std::string ParserChunkSSL::Description()
{
	return ("SSL parser");
}
