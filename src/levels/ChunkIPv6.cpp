
#include "ChunkIPv6.h"

ChunkIPv6::ChunkIPv6(Quilt *data
		, Quilt *containedData
		, ChunkEtherNetDIX *parent
		, IPv6Addr *srcIP
		, IPv6Addr *dstIP)
	: Chunk(data, containedData, parent)
	, SrcIP(srcIP)
	, DstIP(dstIP)
	, Protocol(0)	// TODO
{
}

ChunkIPv6::~ChunkIPv6()
{
	delete SrcIP;
	delete DstIP;
}
