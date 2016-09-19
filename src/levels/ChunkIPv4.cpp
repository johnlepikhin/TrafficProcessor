
#include "ChunkIPv4.h"

ChunkIPv4::ChunkIPv4(const Quilt *data
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
		, unsigned short ttl)
	: Chunk(data, containedData, parent)
	, IHL32bit(iHL32bit)
	, SrcIP(srcIP)
	, DstIP(dstIP)
	, PktLength(pktLength)
	, Protocol(protocol)
	, FlagDontFragment(flagDontFragment)
	, FlagIsFragmented(flagIsFragmented)
	, ID(id)
	, FragmentOffset(fragmentOffset)
	, TTL(ttl)
{
}

ChunkIPv4::~ChunkIPv4()
{
	delete SrcIP;
	delete DstIP;
}
