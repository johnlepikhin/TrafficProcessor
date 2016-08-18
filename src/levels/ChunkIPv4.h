
#ifndef SRC_LEVELS_CHUNKIPV4_H_
#define SRC_LEVELS_CHUNKIPV4_H_

#include "../types/IPv4Addr.h"
#include "../types/Chunk.h"
#include "ChunkEtherNetDIX.h"

/**
 * Container for IPv4 chunk
 */
class ChunkIPv4: public Chunk {
public:
	/**
	 * Constructor
	 * @param data Reference to Data from where chunk was read
	 * @param dataPosition Offset of chunk beginning in Data
	 * @param parent Optional reference to parent Chunk
	 * @param iHL32bit Header length in 32-bit words
	 * @param srcIP Source IP address
	 * @param dstIP Destination IP address
	 * @param pktLength Full packet length
	 * @param protocol Next protocol ID
	 */
	ChunkIPv4(Data *data
			, const unsigned long dataPosition
			, ChunkEtherNetDIX *parent
			, unsigned char iHL32bit
			, IPv4Addr *srcIP
			, IPv4Addr *dstIP
			, unsigned short pktLength
			, unsigned char protocol);

	/**
	 * Header length in 32-bit words
	 */
	unsigned char IHL32bit;

	/**
	 * Source IP address
	 */
	IPv4Addr *SrcIP;

	/**
	 * Destination IP address
	 */
	IPv4Addr *DstIP;

	/**
	 * Full packet length
	 */
	unsigned short PktLength;

	/**
	 * Next protocol ID
	 */
	unsigned char Protocol;
};

#endif /* SRC_LEVELS_CHUNKIPV4_H_ */
