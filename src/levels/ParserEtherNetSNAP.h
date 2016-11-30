
#ifndef SRC_LEVELS_PARSERETHERNETSNAP_H_
#define SRC_LEVELS_PARSERETHERNETSNAP_H_

#include "ChunkEtherNetSNAP.h"
#include "ChunkEtherNet.h"
#include "../types/Processor.h"

/**
 * Parser of SNAP EtherNet frame
 */
//lint -sem(ParserEtherNetSNAP::Process, 1p)
//lint -sem(ParserEtherNetSNAP::Process, 2p)
class ParserEtherNetSNAP: public Processor<ChunkEtherNet, ChunkEtherNetSNAP> {
public:
	/**
	 * Try to get EtherNet SNAP frame from data.
	 * @param parent Optional reference to parent Chunk
	 * @return NULL or parsed chunk
	 */
	std::shared_ptr<ChunkEtherNetSNAP> Process(const std::shared_ptr<ChunkEtherNet> &parent);

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

#endif /* SRC_LEVELS_PARSERETHERNETSNAP_H_ */
