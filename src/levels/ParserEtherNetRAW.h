
#ifndef SRC_LEVELS_PARSERETHERNETRAW_H_
#define SRC_LEVELS_PARSERETHERNETRAW_H_

#include "../types/Chunk.h"
#include "ChunkEtherNetRAW.h"

/**
 * Parser of RAW EtherNet frame
 */
//lint -sem(ParserEtherNetRAW::DoParse, 1p)
//lint -sem(ParserEtherNetRAW::DoParse, 2p)
class ParserEtherNetRAW: public Processor {
public:
	/**
	 * Try to get EtherNet DIX frame from data.
	 * @param data Reference to Data from where chunk was read
	 * @param parent Optional reference to parent Chunk
	 * @return NULL or parsed chunk
	 */
	ChunkEtherNetRAW *DoParse(Data *data, ChunkEtherNet *parent);

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
