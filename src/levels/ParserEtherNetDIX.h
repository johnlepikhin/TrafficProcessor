
#ifndef SRC_LEVELS_PARSERETHERNETDIX_H_
#define SRC_LEVELS_PARSERETHERNETDIX_H_

#include "ChunkEtherNetDIX.h"
#include "../types/Processor.h"

/**
 * Parser of DIX EtherNet frame
 */
class ParserEtherNetDIX: public Processor<ChunkEtherNet, ChunkEtherNetDIX> {
public:
	/**
	 * Try to get EtherNet DIX frame from data.
	 * @param parent Optional reference to parent Chunk
	 * @return NULL or parsed chunk
	 */
	std::shared_ptr<ChunkEtherNetDIX> Process(const std::shared_ptr<ChunkEtherNet> &parent);

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

#endif /* SRC_LEVELS_PARSERETHERNETDIX_H_ */
