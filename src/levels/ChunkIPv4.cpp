
#include "ChunkIPv4.h"
#include "../core/utils.h"

ChunkIPv4::ChunkIPv4(BaseQuilt baseData
		, PayloadQuilt payload
		, std::shared_ptr<ChunkEtherNetDIX> parent
		, unsigned char iHL32bit
		, const unsigned long srcIP
		, const unsigned long dstIP
		, unsigned short pktLength
		, unsigned short payloadLength
		, unsigned char protocol
		, bool flagDontFragment
		, bool flagIsFragmented
		, unsigned short id
		, unsigned short fragmentOffset
		, unsigned short ttl)
	: Chunk(baseData, payload, parent)
	, IHL32bit(iHL32bit)
	, SrcIP(srcIP)
	, DstIP(dstIP)
	, PktLength(pktLength)
	, PayloadLength(payloadLength)
	, FlagDontFragment(flagDontFragment)
	, FlagIsFragmented(flagIsFragmented)
	, ID(id)
	, FragmentOffset(fragmentOffset)
	, TTL(ttl)
	, Protocol (protocol)
{
}

std::string ChunkIPv4::StringOfSrcIP()
{
	return (IPv4Addr::asString(SrcIP));
}

std::string ChunkIPv4::StringOfDstIP()
{
	return (IPv4Addr::asString(DstIP));
}

std::string ChunkIPv4::BinaryOfIP(unsigned long ip)
{
	std::string r;
	r.resize(4);
	r[0]=(ip >> 24) & 0xff;
	r[1]=(ip >> 16) & 0xff;
	r[2]=(ip >> 8) & 0xff;
	r[3]=ip & 0xff;

	return (r);
}
