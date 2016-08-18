
#ifndef SRC_LEVELS_CHUNKIPv6_H_
#define SRC_LEVELS_CHUNKIPv6_H_

#include "../types/IPv6Addr.h"
#include "../types/Chunk.h"
#include "ChunkEtherNetDIX.h"

/**
 * Container for IPv6 chunk
 */
class ChunkIPv6: public Chunk {
public:
	/**
	 * Constructor
	 * @param data Reference to Data from where chunk was read
	 * @param dataPosition Offset of chunk beginning in Data
	 * @param parent Optional reference to parent Chunk
	 * @param srcIP Source IP address
	 * @param dstIP Destination IP address
	 */
	ChunkIPv6(Data *data
			, const unsigned long dataPosition
			, ChunkEtherNetDIX *parent
			, IPv6Addr *srcIP
			, IPv6Addr *dstIP);

	/**
	 * Source IP address
	 */
	IPv6Addr *SrcIP;

	/**
	 * Destination IP address
	 */
	IPv6Addr *DstIP;
	/**
	 * Next protocol ID
	 */
	unsigned char Protocol;
};

#endif /* SRC_LEVELS_CHUNKIPv6_H_ */
