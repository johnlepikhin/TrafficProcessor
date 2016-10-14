
#ifndef SRC_LEVELS_PARSERETHERNET802LLC_H_
#define SRC_LEVELS_PARSERETHERNET802LLC_H_

#include "../types/Processor.h"
#include "ChunkEtherNet.h"
#include "ChunkEtherNet802LLC.h"

/**
 * Parser of 802.3 LLC EtherNet frame
 */
//lint -sem(ParserEtherNet802LLC::Process, 1p)
//lint -sem(ParserEtherNet802LLC::Process, 2p)
class ParserEtherNet802LLC: public Processor<ChunkEtherNet, ChunkEtherNet802LLC> {
public:
	/**
	 * Try to get EtherNet 802.3 LLC frame from data.
	 * @param parent Optional reference to parent Chunk
	 * @return NULL or parsed chunk
	 */
	std::shared_ptr<ChunkEtherNet802LLC> Process(std::shared_ptr<ChunkEtherNet> parent);

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
