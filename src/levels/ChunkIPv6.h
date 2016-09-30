
#ifndef SRC_LEVELS_CHUNKIPv6_H_
#define SRC_LEVELS_CHUNKIPv6_H_

#include "../types/IPv6Addr.h"
#include "../types/Chunk.h"
#include "ChunkEtherNetDIX.h"
#include "ChunkIPTraits.h"

/**
 * Container for IPv6 chunk
 */
class ChunkIPv6: public Chunk<ChunkEtherNetDIX>, public ChunkIPTraits {
public:
	/**
	 * Constructor
	 * @param data Reference to Data from where chunk was read
	 * @param parent Optional reference to parent Chunk
	 * @param srcIP Source IP address
	 * @param dstIP Destination IP address
	 */
	ChunkIPv6(BaseQuilt baseData
			, PayloadQuilt payload
			, std::shared_ptr<ChunkEtherNetDIX> parent
			, IPv6Addr *srcIP
			, IPv6Addr *dstIP);

	~ChunkIPv6();

	/**
	 * Source IP address
	 */
	IPv6Addr *SrcIP;

	/**
	 * Destination IP address
	 */
	IPv6Addr *DstIP;
};

#endif /* SRC_LEVELS_CHUNKIPv6_H_ */
