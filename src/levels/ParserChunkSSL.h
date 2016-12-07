
#ifndef SRC_LEVELS_PARSERCHUNKSSL_H_
#define SRC_LEVELS_PARSERCHUNKSSL_H_

#include "ChunkSSL.h"

class ParserChunkSSL: public Processor<SessionTCP, ChunkSSL> {
private:
	std::unique_ptr<SSLAlert> AlertParser(const std::shared_ptr<SessionTCP> &session
			, const std::shared_ptr<EndPoint> &flow
			, const std::string *preview);
	std::unique_ptr<SSLHello> HelloParser(const std::string *preview);
	std::unique_ptr<SSLCertificate> CertificateParser(const std::string *preview);
	std::unique_ptr<SSLHandshake> HandshakeParser(const std::shared_ptr<SessionTCP> &session
			, const std::shared_ptr<EndPoint> &flow
			, const std::string *preview
			, const uint16_t recordLength);
	std::shared_ptr<ChunkSSL> FlowParser(const std::shared_ptr<SessionTCP> &session
			, const std::shared_ptr<EndPoint> &flow);
public:
	/**
	 * Parse SSL data
	 * @param session Reference to TCP session
	 * @return NULL or parsed chunk
	 */
	std::shared_ptr<ChunkSSL> Process(const std::shared_ptr<SessionTCP> &session);

	/**
	 * Returns unique ID for this Parser
	 * @return ID
	 */
	std::string ID();

	/**
	 * Returns description for this Parser
	 * @return Description
	 */
	std::string Description();
};

#endif /* SRC_LEVELS_PARSERCHUNKSSL_H_ */
