
#ifndef SRC_LEVELS_CHUNKIPv6_H_
#define SRC_LEVELS_CHUNKIPv6_H_

#include "../types/IPv6Addr.h"
#include "../types/Chunk.h"
#include "../types/PhantomQuilt.h"
#include "ChunkEtherNetDIX.h"

class IPv6HeaderFragment {
public:
	IPv6HeaderFragment(unsigned short fragmentOffset
			, bool hasNextFragments
			, unsigned long packetID)
		: FragmentOffset(fragmentOffset)
		, HasNextFragments(hasNextFragments)
		, PacketID(packetID)
	{ };

	unsigned short FragmentOffset;
	bool HasNextFragments;
	unsigned long PacketID;
};

/**
 * Container for IPv6 chunk
 */
class ChunkIPv6: public Chunk<ChunkEtherNetDIX> {
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
			, IPv6Addr srcIP
			, IPv6Addr dstIP
			, unsigned char protocol
			, unsigned char trafficClass
			, unsigned long flowLabel
			, unsigned char hopLimit
			, std::shared_ptr<IPv6HeaderFragment> hdrFragment
			, unsigned long payloadLength
			);

	/**
	 * Source IP address
	 */
	IPv6Addr SrcIP;

	/**
	 * Destination IP address
	 */
	IPv6Addr DstIP;

	unsigned char TrafficClass;
	unsigned long FlowLabel;
	unsigned char HopLimit;
	unsigned long PayloadLength;

	std::shared_ptr<IPv6HeaderFragment> HdrFragment;

	/**
	 * Protocol of next level
	 */
	unsigned short Protocol;

	std::string StringOfSrcIP() { return (SrcIP.AsString()); };
	std::string StringOfDstIP() { return (DstIP.AsString()); };
	inline std::string BinaryOfSrcIP() { return (SrcIP.AsBinary()); };
	inline std::string BinaryOfDstIP() { return (DstIP.AsBinary()); };
};

#endif /* SRC_LEVELS_CHUNKIPv6_H_ */
