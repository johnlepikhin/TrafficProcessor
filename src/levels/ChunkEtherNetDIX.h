
#ifndef SRC_LEVELS_CHUNKETHERNETDIX_H_
#define SRC_LEVELS_CHUNKETHERNETDIX_H_

#include "ChunkEtherNet.h"

/**
 * Container for DIX EtherNet frame
 */
class ChunkEtherNetDIX: public Chunk<ChunkEtherNet> {
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
			, const unsigned short etherType);

	/**
	 * 2-byte value at offset 13, ethernet type (/etc/ethertypes in Debian)
	 */
	const unsigned short EtherNetType;
};

#endif /* SRC_LEVELS_CHUNKETHERNETDIX_H_ */
