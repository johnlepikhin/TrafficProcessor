
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
	 * @param parent Optional reference to parent Chunk
	 * @param iHL32bit Header length in 32-bit words
	 * @param srcIP Source IP address
	 * @param dstIP Destination IP address
	 * @param pktLength Full packet length
	 * @param protocol Next protocol ID
	 * @param flagDontFragment True if packet cannot be fragmented
	 * @param flagIsFragmented True if there are another fragments for this packet
	 * @param id Identifier of packet (the same in all fragments)
	 * @param fragmentOffset offset of this fragment in bytes
	 * @param ttl TTL
	 */
	ChunkIPv4(const Quilt *data
			, const Quilt *containedData
			, const ChunkEtherNetDIX *parent
			, unsigned char iHL32bit
			, const IPv4Addr *srcIP
			, const IPv4Addr *dstIP
			, unsigned short pktLength
			, unsigned char protocol
			, bool flagDontFragment
			, bool flagIsFragmented
			, unsigned short id
			, unsigned short fragmentOffset
			, unsigned short ttl);

	~ChunkIPv4();

	/**
	 * Header length in 32-bit words
	 */
	unsigned char IHL32bit;

	/**
	 * Source IP address
	 */
	const IPv4Addr *SrcIP;

	/**
	 * Destination IP address
	 */
	const IPv4Addr *DstIP;

	/**
	 * Full packet length
	 */
	unsigned short PktLength;

	/**
	 * Next protocol ID
	 */
	unsigned char Protocol;

	/**
	 * True if DontFragment flag is set
	 */
	bool FlagDontFragment;

	/**
	 * True if packet is fragmented
	 */
	bool FlagIsFragmented;

	/**
	 * ID of IP packet
	 */
	unsigned short ID;

	/**
	 * Offset of the fragment in bytes
	 */
	unsigned short FragmentOffset;

	/**
	 * TTL
	 */
	unsigned short TTL;
};

#endif /* SRC_LEVELS_CHUNKIPV4_H_ */
