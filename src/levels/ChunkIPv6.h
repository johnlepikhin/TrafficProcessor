
#ifndef SRC_LEVELS_CHUNKIPv6_H_
#define SRC_LEVELS_CHUNKIPv6_H_

#include "../types/IPv6Addr.h"
#include "../types/Chunk.h"
#include "../types/PhantomQuilt.h"
#include "ChunkEtherNetTraits.h"

/**
 * Representation of Fragment extra header
 */
class IPv6HeaderFragment {
public:
	/**
	 * Constructor
	 * @param fragmentOffset Offset of fragment in payload
	 * @param hasNextFragments False if this is last fragment
	 * @param packetID Packet identifier
	 */
	IPv6HeaderFragment(uint16_t fragmentOffset
			, bool hasNextFragments
			, uint32_t packetID)
		: FragmentOffset(fragmentOffset)
		, HasNextFragments(hasNextFragments)
		, PacketID(packetID)
	{ };

	/**
	 * Offset of fragment
	 */
	unsigned short FragmentOffset;

	/**
	 * False if this is last fragment
	 */
	bool HasNextFragments;

	/**
	 * Packet identifier
	 */
	uint32_t PacketID;
};

/**
 * Container for IPv6 chunk
 */
class ChunkIPv6: public Chunk<ChunkEtherNetTraits> {
public:
	/**
	 * Constructor
	 * @param baseData Reference to Data from where chunk was read
	 * @param payload Reference to payload of this frame
	 * @param parent Optional reference to parent Chunk
	 * @param srcIP Source IP address
	 * @param dstIP Destination IP address
	 * @param protocol Protocol of underlying layer
	 * @param trafficClass Traffic class
	 * @param flowLabel Flow label
	 * @param hopLimit Hop limit
	 * @param hdrFragment Pointer to optional Fragment extra header
	 * @param payloadLength Length of payload
	 */
	ChunkIPv6(const BaseQuilt &baseData
			, const PayloadQuilt &payload
			, const std::shared_ptr<ChunkEtherNetTraits> &parent
			, const IPv6Addr &srcIP
			, const IPv6Addr &dstIP
			, unsigned char protocol
			, unsigned char trafficClass
			, uint32_t flowLabel
			, unsigned char hopLimit
			, const std::shared_ptr<IPv6HeaderFragment> &hdrFragment
			, uint32_t payloadLength
			);

	/**
	 * Source IP address
	 */
	IPv6Addr SrcIP;

	/**
	 * Destination IP address
	 */
	IPv6Addr DstIP;

	/**
	 * Traffic class
	 */
	unsigned char TrafficClass;

	/**
	 * Flow label
	 */
	uint32_t FlowLabel;

	/**
	 * Hop limit
	 */
	unsigned char HopLimit;

	/**
	 * Length of payload
	 */
	uint32_t PayloadLength;

	/**
	 * Pointer to optional extra header Fragment
	 */
	std::shared_ptr<IPv6HeaderFragment> HdrFragment;

	/**
	 * Protocol of next level
	 */
	unsigned short Protocol;

	/**
	 * Get source IP in human readable format
	 * @return source IP address as string
	 */
	std::string StringOfSrcIP() { return (SrcIP.AsString()); };

	/**
	 * Get destination IP in human readable format
	 * @return destination IP address as string
	 */
	std::string StringOfDstIP() { return (DstIP.AsString()); };

	/**
	 * Get source IP as bytes
	 * @return source IP address as bytes
	 */
	inline std::string BinaryOfSrcIP() { return (SrcIP.AsBinary()); };

	/**
	 * Get destination IP as bytes
	 * @return destination  IP address as bytes
	 */
	inline std::string BinaryOfDstIP() { return (DstIP.AsBinary()); };
};

#endif /* SRC_LEVELS_CHUNKIPv6_H_ */
