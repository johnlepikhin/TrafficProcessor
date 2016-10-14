
#ifndef SRC_LEVELS_PARSERETHERNETRAW_H_
#define SRC_LEVELS_PARSERETHERNETRAW_H_

#include "ChunkEtherNetRAW.h"
#include "ChunkEtherNet.h"
#include "../types/Processor.h"

/**
 * Parser of RAW EtherNet frame
 */
//lint -sem(ParserEtherNetRAW::Process, 1p)
//lint -sem(ParserEtherNetRAW::Process, 2p)
class ParserEtherNetRAW: public Processor<ChunkEtherNet, ChunkEtherNetRAW> {
public:
	/**
	 * Try to get EtherNet DIX frame from data.
	 * @param parent Optional reference to parent Chunk
	 * @return NULL or parsed chunk
	 */
	std::shared_ptr<ChunkEtherNetRAW> Process(std::shared_ptr<ChunkEtherNet> parent);

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

#endif /* SRC_LEVELS_PARSERETHERNETRAW_H_ */
