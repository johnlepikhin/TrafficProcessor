
#ifndef SRC_LEVELS_PARSERPACKETMYSQL_H_
#define SRC_LEVELS_PARSERPACKETMYSQL_H_

#include "TCPSessionFollowerHolder.h"
#include "../types/Chunk.h"
#include "SessionTCP.h"
#include <pcrecpp.h>

#include "PacketMySQL.h"

/**
 * Parser of MySQL packets
 */
class ParserPacketMySQL: public TCPSessionFollowerHolder<PacketMySQL> {
private:
	pcrecpp::RE QueryCheckRe;
	uint32_t GetPayloadLength(const std::shared_ptr<EndPoint> &flow);
	std::string ReadStringNULL(const std::string &payload, size_t offset);
	std::string ReadPacketPreview(uint32_t length, const std::shared_ptr<EndPoint> &flow);

	std::shared_ptr<PacketMySQL> ParseClient(
			const std::shared_ptr<SessionTCP> &session
			, const std::shared_ptr<PacketMySQL> chunk
			, const std::shared_ptr<EndPoint> &flow);

	std::shared_ptr<PacketMySQL> ParseServer(
			const std::shared_ptr<SessionTCP> &session
			, std::shared_ptr<PacketMySQL> chunk
			, const std::shared_ptr<EndPoint> &flow);

	std::shared_ptr<PacketMySQL> ParseHandshakeResponse(
			const std::shared_ptr<SessionTCP> &session
			, std::shared_ptr<PacketMySQL> chunk
			, const std::string &payload
			, uint32_t packetLength);

	std::shared_ptr<PacketMySQL> ParseCommand(
			const std::shared_ptr<SessionTCP> &session
			, std::shared_ptr<PacketMySQL> chunk
			, const std::string &payload
			, uint32_t packetLength);

	std::shared_ptr<PacketMySQL> DefaultCase(
			const std::shared_ptr<SessionTCP> &session
			, std::shared_ptr<PacketMySQL> chunk
			, uint32_t packetLength);
public:
	ParserPacketMySQL();

	/**
	 * Read HTTP request from data.
	 * @param session Reference to TCP session
	 * @return NULL or parsed chunk
	 */
	std::shared_ptr<PacketMySQL> FollowerProcess(const std::shared_ptr<SessionTCP> &session, std::shared_ptr<PacketMySQL> follower);

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
