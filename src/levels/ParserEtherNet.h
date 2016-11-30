
#ifndef SRC_LEVELS_PARSERETHERNET_H_
#define SRC_LEVELS_PARSERETHERNET_H_

#include "../types/Processor.h"
#include "ChunkEtherNet.h"

/**
 * Parser of base EtherNet frame
 */
class ParserEtherNet : public Processor<CBaseQuilt, ChunkEtherNet> {
public:
	/**
	 * Parser
	 * @param payload Reference to base PCAP frame
	 * @return ChunkEtherNet on success or nullptr
	 */
	std::shared_ptr<ChunkEtherNet> Process(const BaseQuilt &payload);

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
