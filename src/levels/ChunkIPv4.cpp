
#include "ChunkIPv4.h"

ChunkIPv4::ChunkIPv4(Data *data
		, const unsigned long dataPosition
		, ChunkEtherNetDIX *parent
		, unsigned char iHL32bit
		, IPv4Addr *srcIP
		, IPv4Addr *dstIP
		, unsigned short pktLength
		, unsigned char protocol)
	: Chunk(data, dataPosition, parent)
	, IHL32bit(iHL32bit)
	, SrcIP(srcIP)
	, DstIP(dstIP)
	, PktLength(pktLength)
	, Protocol(protocol)
{
}
