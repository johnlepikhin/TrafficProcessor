
#ifndef SRC_LEVELS_CHUNKIPV4_H_
#define SRC_LEVELS_CHUNKIPV4_H_

#include "../types/IPv4Addr.h"
#include "../types/Chunk.h"
#include "ChunkEtherNetTraits.h"

/**
 * Container for IPv4 chunk
 */
class ChunkIPv4: public Chunk<ChunkEtherNetTraits> {
public:
	/**
	 * Constructor
	 * @param baseData Reference to Data from where chunk was read
	 * @param payload Reference to payload of this frame
	 * @param parent Optional reference to parent Chunk
	 * @param iHL32bit Header length in 32-bit words
	 * @param srcIP Source IP address
	 * @param dstIP Destination IP address
	 * @param pktLength Full packet length
	 * @param payloadLength Length of payload
	 * @param protocol Next protocol ID
	 * @param flagDontFragment True if packet cannot be fragmented
	 * @param flagIsFragmented True if there are another fragments for this packet
	 * @param id Identifier of packet (the same in all fragments)
	 * @param fragmentOffset offset of this fragment in bytes
	 * @param ttl TTL
	 */
	ChunkIPv4(const BaseQuilt &baseData
			, const PayloadQuilt &payload
			, const std::shared_ptr<ChunkEtherNetTraits> &parent
			, unsigned char iHL32bit
			, const uint32_t srcIP
			, const uint32_t dstIP
			, unsigned short pktLength
			, unsigned short payloadLength
			, unsigned char protocol
			, bool flagDontFragment
			, bool flagIsFragmented
			, unsigned short id
			, unsigned short fragmentOffset
			, unsigned short ttl);

	/**
	 * Header length in 32-bit words
	 */
	unsigned char IHL32bit;

	/**
	 * Source IP address
	 */
	const uint32_t SrcIP;

	/**
	 * Destination IP address
	 */
	const uint32_t DstIP;

	/**
	 * Full packet length
	 */
	unsigned short PktLength;

	/**
	 * Payload length
	 */
	unsigned short PayloadLength;

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

	/**
	 * Protocol of next level
	 */
	unsigned short Protocol;

	/**
	 * Get source IP in human readable format
	 * @return source IP address as string
	 */
	std::string StringOfSrcIP();

	/**
	 * Get destination IP in human readable format
	 * @return destination IP address as string
	 */
	std::string StringOfDstIP();

	/**
	 * Get source IP as bytes
	 * @return source IP address as bytes
	 */
	inline std::string BinaryOfSrcIP() { return (BinaryOfIP(SrcIP)); };

	/**
	 * Get destination IP as bytes
	 * @return destination  IP address as bytes
	 */
	inline std::string BinaryOfDstIP() { return (BinaryOfIP(DstIP)); };
private:
	std::string BinaryOfIP(uint32_t ip);
};

#endif /* SRC_LEVELS_CHUNKIPV4_H_ */
