
#ifndef SRC_LEVELS_PARSERPACKETMYSQL_H_
#define SRC_LEVELS_PARSERPACKETMYSQL_H_

#include "../types/Processor.h"
#include "../types/Chunk.h"
#include "SessionTCP.h"
#include <pcrecpp.h>

#include "PacketMySQL.h"

/**
 * Parser of MySQL packets
 */
class ParserPacketMySQL: public Processor<SessionTCP, PacketMySQL> {
private:
	pcrecpp::RE QueryCheckRe;
	uint32_t GetPayloadLength(std::shared_ptr<EndPoint> flow);
	std::string ReadStringNULL(std::string payload, size_t offset);
	std::string ReadPacketPreview(uint32_t length, std::shared_ptr<EndPoint> flow);

	std::shared_ptr<PacketMySQL> ParseClient(
			std::shared_ptr<SessionTCP> session
			, std::shared_ptr<EndPoint> flow);

	std::shared_ptr<PacketMySQL> ParseServer(
			std::shared_ptr<SessionTCP> session
			, std::shared_ptr<EndPoint> flow);

	std::shared_ptr<PacketMySQL> ParseHandshakeResponse(
			std::shared_ptr<SessionTCP> session
			, std::string payload
			, uint32_t packetLength);

	std::shared_ptr<PacketMySQL> ParseCommand(
			std::shared_ptr<SessionTCP> session
			, std::string payload
			, uint32_t packetLength);

	std::shared_ptr<PacketMySQL> DefaultCase(
			std::shared_ptr<SessionTCP> session
			, uint32_t packetLength);
public:
	ParserPacketMySQL();

	/**
	 * Read HTTP request from data.
	 * @param session Reference to TCP session
	 * @return NULL or parsed chunk
	 */
	std::shared_ptr<PacketMySQL> Process(std::shared_ptr<SessionTCP> session);

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

#endif /* SRC_LEVELS_PARSERPACKETMYSQL_H_ */
