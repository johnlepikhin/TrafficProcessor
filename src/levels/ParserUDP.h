
#ifndef SRC_LEVELS_PARSERUDP_H_
#define SRC_LEVELS_PARSERUDP_H_

#include "PacketIPv4.h"
#include "ChunkUDP.h"
#include "../types/Processor.h"

/**
 * Parser for UDP datagrams
 */
class ParserUDP: public Processor<PacketIPVariant, ChunkUDP> {
public:
	/**
	 * Try to get UDP from data.
	 * @param data Reference to Data from where chunk was read
	 * @param parent Optional reference to parent Chunk
	 * @return NULL or parsed chunk
	 */
	std::shared_ptr<ChunkUDP> Process(const std::shared_ptr<PacketIPVariant> &parent);

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

#endif /* SRC_LEVELS_PARSERUDP_H_ */
