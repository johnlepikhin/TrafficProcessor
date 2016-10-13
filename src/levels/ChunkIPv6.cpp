
#include "ChunkIPv6.h"
#include "ChunkIPTraits.h"

ChunkIPv6::ChunkIPv6(BaseQuilt baseData
		, PayloadQuilt payload
		, std::shared_ptr<ChunkEtherNetDIX> parent
		, IPv6Addr srcIP
		, IPv6Addr dstIP
		, unsigned char protocol
		, unsigned char trafficClass
		, unsigned long flowLabel
		, unsigned char hopLimit
		, std::shared_ptr<IPv6HeaderFragment> hdrFragment
		, unsigned long payloadLength)
	: Chunk<ChunkEtherNetDIX>(baseData, payload, parent)
	, ChunkIPTraits(protocol, parent)
	, SrcIP(srcIP)
	, DstIP(dstIP)
	, TrafficClass(trafficClass)
	, FlowLabel(flowLabel)
	, HopLimit(hopLimit)
	, PayloadLength(payloadLength)
	, HdrFragment(hdrFragment)
{
	Protocol = protocol;
}
