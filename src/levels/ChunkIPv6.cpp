
#include "ChunkIPv6.h"
#include "ChunkIPTraits.h"

ChunkIPv6::ChunkIPv6(BaseQuilt baseData
		, PayloadQuilt payload
		, std::shared_ptr<ChunkEtherNetDIX> parent
		, IPv6Addr *srcIP
		, IPv6Addr *dstIP)
	: Chunk<ChunkEtherNetDIX>(baseData, payload, parent)
	, ChunkIPTraits(0)	// TODO
	, SrcIP(srcIP)
	, DstIP(dstIP)
{
}

ChunkIPv6::~ChunkIPv6()
{
	delete SrcIP;
	delete DstIP;
}
