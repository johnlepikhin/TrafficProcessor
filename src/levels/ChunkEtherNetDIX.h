
#ifndef SRC_LEVELS_CHUNKETHERNETDIX_H_
#define SRC_LEVELS_CHUNKETHERNETDIX_H_

#include "ChunkEtherNetTraits.h"

/**
 * Container for DIX EtherNet frame
 */
class ChunkEtherNetDIX: public ChunkEtherNetTraits {
public:
	/**
	 * Constructor for DIX
	 * @param baseData Reference to Data from where chunk was read
	 * @param payload Reference to payload of this frame
	 * @param parent Optional reference to parent Chunk
	 * @param etherType EtherNet type (OSI level 3 type)
	 */
	ChunkEtherNetDIX(const BaseQuilt &baseData
			, const PayloadQuilt &payload
			, const std::shared_ptr<ChunkEtherNet> &parent
			, const uint16_t etherType);

};

#endif /* SRC_LEVELS_CHUNKETHERNETDIX_H_ */
