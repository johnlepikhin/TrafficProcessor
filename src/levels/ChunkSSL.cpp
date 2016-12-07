// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "ChunkSSL.h"

SSLAlert::SSLAlert(SSLAlertSeverity severity, SSLAlertDescription description)
	: Severity(severity)
	, Description(description)
{

}

SSLHello::SSLHello(uint16_t version
			, uint32_t random
			, uint8_t sessionIDLength
			, uint32_t sessionID)
	: Random(random)
	, SessionID(sessionID)
	, Version(version)
	, SessionIDLength(sessionIDLength)
{

}

SSLCertificate::SSLCertificate(std::vector<std::string> certificates)
	: Certificates(certificates)
{

}

SSLHandshake::SSLHandshake(SSLHandshakeType handshakeType
			, uint32_t length
			, std::unique_ptr<SSLHello> hello
			, std::unique_ptr<SSLCertificate> certificate)
	: HandshakeType(handshakeType)
	, Length(length)
	, Hello(std::move(hello))
	, Certificate(std::move(certificate))
{

}

ChunkSSL::ChunkSSL(const std::shared_ptr<SessionTCP> &parent
			, SSLRecordType recordType
			, uint16_t version
			, uint16_t dataLength
			, std::unique_ptr<SSLAlert> alert
			, std::unique_ptr<SSLHandshake> handshake)
	: Chunk<SessionTCP>(parent->BaseData, parent->Client->Payload, parent)
	, RecordType(recordType)
	, Version(version)
	, DataLength(dataLength)
	, Alert(std::move(alert))
	, Handshake(std::move(handshake))
{

}
