
#ifndef SRC_LEVELS_PARSERETHERNET_H_
#define SRC_LEVELS_PARSERETHERNET_H_

#include "ChunkEtherNet.h"

/**
 * Parser of base EtherNet frame
 */
class ParserEtherNet : public Processor {
public:
	/**
	 * Try to get EtherNet frame from data.
	 * @param data Reference to Data from where chunk was read
	 * @param parent Optional reference to parent Chunk
	 * @return NULL or parsed chunk
	 */
	ChunkEtherNet *DoParse(Data *data, Chunk *parent);

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


#endif /* SRC_LEVELS_PARSERETHERNET_H_ */
