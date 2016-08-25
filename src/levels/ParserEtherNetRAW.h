
#ifndef SRC_LEVELS_PARSERETHERNETRAW_H_
#define SRC_LEVELS_PARSERETHERNETRAW_H_

#include "../types/Chunk.h"
#include "ChunkEtherNetRAW.h"

/**
 * Parser of RAW EtherNet frame
 */
//lint -sem(ParserEtherNetRAW::Process, 1p)
//lint -sem(ParserEtherNetRAW::Process, 2p)
class ParserEtherNetRAW: public Processor {
public:
	/**
	 * Try to get EtherNet DIX frame from data.
	 * @param data Reference to Data from where chunk was read
	 * @param parent Optional reference to parent Chunk
	 * @return NULL or parsed chunk
	 */
	ChunkEtherNetRAW *Process(Data *data, Chunk *parent);

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
