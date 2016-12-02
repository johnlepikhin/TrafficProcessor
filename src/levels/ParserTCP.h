
#ifndef SRC_LEVELS_PARSERTCP_H_
#define SRC_LEVELS_PARSERTCP_H_

#include "PacketIPv4.h"
#include "ChunkTCP.h"
#include "../types/Processor.h"

/**
 * Parser for TCP fragments
 */
class ParserTCP: public Processor<PacketIPVariant, ChunkTCP> {
public:
	/**
	 * Try to get TCP from data.
	 * @param data Reference to Data from where chunk was read
	 * @param parent Optional reference to parent Chunk
	 * @return NULL or parsed chunk
	 */
	std::shared_ptr<ChunkTCP> Process(const std::shared_ptr<PacketIPVariant> &parent);

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

#endif /* SRC_LEVELS_PARSERTCP_H_ */
