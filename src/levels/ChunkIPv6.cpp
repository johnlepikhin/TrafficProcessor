
#include "ChunkIPv6.h"

ChunkIPv6::ChunkIPv6(Data *data
		, const unsigned long dataPosition
		, ChunkEtherNetDIX *parent
		, IPv6Addr *srcIP
		, IPv6Addr *dstIP)
	: Chunk(data, dataPosition, parent)
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
