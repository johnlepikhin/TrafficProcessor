
#ifndef SRC_LEVELS_PARSERIPv6_H_
#define SRC_LEVELS_PARSERIPv6_H_

#include "../types/Chunk.h"
#include "ChunkIPv6.h"

/**
 * Parser for IPv6 protocol
 */
//lint -sem(ParserIPv6::Process, 1p)
//lint -sem(ParserIPv6::Process, 2p)
class ParserIPv6: public Processor {
public:
	/**
	 * Try to get IPv6 from data.
	 * @param data Reference to Data from where chunk was read
	 * @param parent Optional reference to parent Chunk
	 * @return NULL or parsed chunk
	 */
	ChunkIPv6 *Process(Data *data, ChunkEtherNetDIX *parent);

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
