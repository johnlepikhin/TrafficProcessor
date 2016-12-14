
#ifndef SRC_LEVELS_PARSERIPv6_H_
#define SRC_LEVELS_PARSERIPv6_H_

#include "ChunkIPv6.h"
#include "ChunkEtherNetTraits.h"
#include "../types/Processor.h"

/**
 * Parser for IPv6 protocol
 */
//lint -sem(ParserIPv6::Process, 1p)
//lint -sem(ParserIPv6::Process, 2p)
class ParserIPv6: public Processor<ChunkEtherNetTraits, ChunkIPv6> {
public:
	/**
	 * Try to get IPv6 from data.
	 * @param parent Optional reference to parent Chunk
	 * @return NULL or parsed chunk
	 */
	std::shared_ptr<ChunkIPv6> Process(const std::shared_ptr<ChunkEtherNetTraits> &parent);

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

#endif /* SRC_LEVELS_PARSERIPv6_H_ */
