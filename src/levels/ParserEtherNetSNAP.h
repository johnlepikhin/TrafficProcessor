
#ifndef SRC_LEVELS_PARSERETHERNETSNAP_H_
#define SRC_LEVELS_PARSERETHERNETSNAP_H_

#include "../types/Chunk.h"
#include "ChunkEtherNetSNAP.h"

/**
 * Parser of SNAP EtherNet frame
 */
class ParserEtherNetSNAP: public Processor {
public:
	/**
	 * Try to get EtherNet SNAP frame from data.
	 * @param data Reference to Data from where chunk was read
	 * @param parent Optional reference to parent Chunk
	 * @return NULL or parsed chunk
	 */
	ChunkEtherNetSNAP *DoParse(Data *data, Chunk *parent);

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
