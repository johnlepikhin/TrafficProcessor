
#ifndef SRC_LEVELS_CHUNKETHERNETRAW_H_
#define SRC_LEVELS_CHUNKETHERNETRAW_H_

#include "../types/Chunk.h"
#include "ChunkEtherNetTraits.h"

/**
 * Container for RAW EtherNet frame
 */
class ChunkEtherNetRAW: public ChunkEtherNetTraits {
public:
	/**
	 * Constructor for RAW
	 * @param baseData Reference to Data from where chunk was read
	 * @param payload Reference to payload of this frame
	 * @param parent Optional reference to parent Chunk
	 * @param length Length of payload
	 */
	ChunkEtherNetRAW(const BaseQuilt &baseData
			, const PayloadQuilt &payload
			, const std::shared_ptr<ChunkEtherNet> &parent
			, const unsigned short length);

	/**
	 * Length of payload
	 */
	const unsigned short PayloadLength;
};

#endif /* SRC_LEVELS_CHUNKETHERNETRAW_H_ */
