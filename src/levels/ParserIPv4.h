
#ifndef SRC_LEVELS_PARSERIPV4_H_
#define SRC_LEVELS_PARSERIPV4_H_

#include "ChunkIPv4.h"
#include "ChunkEtherNetDIX.h"
#include "../types/Processor.h"

/**
 * Parser for IPv4 protocol
 */
//lint -sem(ParserIPv4::Process, 1p)
//lint -sem(ParserIPv4::Process, 2p)
class ParserIPv4: public Processor<ChunkEtherNetDIX, ChunkIPv4> {
public:
	/**
	 * Try to get IPv4 from data.
	 * @param data Reference to Data from where chunk was read
	 * @param parent Optional reference to parent Chunk
	 * @return NULL or parsed chunk
	 */
	std::shared_ptr<ChunkIPv4> Process(std::shared_ptr<ChunkEtherNetDIX> parent);

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

#endif /* SRC_LEVELS_PARSERIPV4_H_ */
