
#ifndef SRC_LEVELS_PARSERETHERNET802LLC_H_
#define SRC_LEVELS_PARSERETHERNET802LLC_H_

#include "../types/Chunk.h"
#include "ChunkEtherNet802LLC.h"

/**
 * Parser of 802.3 LLC EtherNet frame
 */
class ParserEtherNet802LLC: public Processor {
public:
	/**
	 * Try to get EtherNet 802.3 LLC frame from data.
	 * @param data Reference to Data from where chunk was read
	 * @param parent Optional reference to parent Chunk
	 * @return NULL or parsed chunk
	 */
	ChunkEtherNet802LLC *DoParse(Data *data, Chunk *parent);

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

#endif /* SRC_LEVELS_PARSERETHERNET802LLC_H_ */