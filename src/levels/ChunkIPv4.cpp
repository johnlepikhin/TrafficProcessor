// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "ChunkIPv4.h"
#include "../core/utils.h"

ChunkIPv4::ChunkIPv4(const BaseQuilt &baseData
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

std::string ChunkIPv4::BinaryOfIP(uint32_t ip)
{
	std::string r;
	r.resize(4); //-V112
	r[0]=(ip >> 24) & 0xff;
	r[1]=(ip >> 16) & 0xff;
	r[2]=(ip >> 8) & 0xff;
	r[3]=ip & 0xff;

	return (r);
}
