
#ifndef SRC_LEVELS_PARSERETHERNET_H_
#define SRC_LEVELS_PARSERETHERNET_H_

#include "../types/Processor.h"
#include "ChunkEtherNet.h"

/**
 * Parser of base EtherNet frame
 */
//lint -sem(ParserEtherNet::Process, 1p)
class ParserEtherNet : public Processor<BaseQuilt, ChunkEtherNet> {
public:
	ChunkEtherNet *Process(BaseQuilt *payload);

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
