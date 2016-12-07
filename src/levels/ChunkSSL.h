
#ifndef SRC_LEVELS_CHUNKSSL_H_
#define SRC_LEVELS_CHUNKSSL_H_

#include "../types/Chunk.h"
#include "SessionTCP.h"
#include <stdint.h>
#include <vector>

enum SSLAlertDescription {
	CLOSE_NOTIFY,
	UNEXPECTED_MESSAGE,
	BAD_RECORD_MAC,
	DECRYPTION_FAILED,
	RECORD_OVERFLOW,
	DECOMPRESSION_FAILURE,
	HANDSHAKE_FAILURE,
	NO_CERTIFICATE,
	BAD_CERTIFICATE,
	UNSUPPORTED_CERTIFICATE,
	CERTIFICATE_REVOKED,
	CERTIFICATE_EXPIRED,
	CERTIFICATE_UNKNOWN,
	ILLEGAL_PARAMETER,
	UNKNOWN_CA,
	ACCESS_DENIED,
	DECODE_ERROR,
	DECRYPT_ERROR,
	EXPORT_RESTRICTION,
	PROTOCOL_VERSION,
	INSUFFICIENT_SECURITY,
	INTERNAL_ERROR,
	USER_CANCELLED,
	NO_RENEGOTIATION
};

enum SSLAlertSeverity {
	WARNING,
	FATAL
};

class SSLAlert {
public:
	SSLAlert(SSLAlertSeverity severity, SSLAlertDescription description);
	SSLAlertSeverity Severity;
	SSLAlertDescription Description;
};

class SSLHello {
public:
	SSLHello(uint16_t version
			, uint32_t random
			, uint8_t sessionIDLength
			, uint32_t sessionID);
	uint32_t Random;
	uint32_t SessionID;
	uint16_t Version;
	uint8_t SessionIDLength;
};

class SSLCertificate {
public:
	SSLCertificate(std::vector<std::string> certificates);
	std::vector<std::string> Certificates;
};

enum SSLHandshakeType {
	HELLO_REQUEST,
	CLIENT_HELLO,
	SERVER_HELLO,
	CERTIFICATE,
	SERVER_KEY_EXCHANGE,
	CERTIFICATE_REQUEST,
	SERVER_DONE,
	CERTIFICATE_VERIFY,
	CLIENT_KEY_EXCHANGE,
	FINISHED
};

class SSLHandshake {
public:
	SSLHandshake(SSLHandshakeType handshakeType
			, uint32_t length
			, std::unique_ptr<SSLHello> hello
			, std::unique_ptr<SSLCertificate> certificate);

	SSLHandshakeType HandshakeType;
	uint32_t Length;
	std::unique_ptr<SSLHello> Hello;
	std::unique_ptr<SSLCertificate> Certificate;

};

enum SSLRecordType {
	CHANGE_CIPHER_SPEC,
	ALERT,
	HANDSHAKE,
	APPLICATION_DATA
};

class ChunkSSL: public Chunk<SessionTCP> {
public:
	ChunkSSL(const std::shared_ptr<SessionTCP> &parent
			, SSLRecordType recordType
			, uint16_t version
			, uint16_t dataLength
			, std::unique_ptr<SSLAlert> alert
			, std::unique_ptr<SSLHandshake> handshake
			);
	SSLRecordType RecordType;
	uint16_t Version;
	uint16_t DataLength;
	std::unique_ptr<SSLAlert> Alert;
	std::unique_ptr<SSLHandshake> Handshake;
};

#endif /* SRC_LEVELS_CHUNKSSL_H_ */
