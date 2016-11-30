// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "ChunkIPv6.h"

ChunkIPv6::ChunkIPv6(const BaseQuilt &baseData
		, const PayloadQuilt &payload
		, const std::shared_ptr<ChunkEtherNetDIX> &parent
		, const IPv6Addr &srcIP
		, const IPv6Addr &dstIP
		, unsigned char protocol
		, unsigned char trafficClass
		, uint32_t flowLabel
		, unsigned char hopLimit
		, const std::shared_ptr<IPv6HeaderFragment> &hdrFragment
		, uint32_t payloadLength)
	: Chunk<ChunkEtherNetDIX>(baseData, payload, parent)
	, SrcIP(srcIP)
	, DstIP(dstIP)
	, TrafficClass(trafficClass)
	, FlowLabel(flowLabel)
	, HopLimit(hopLimit)
	, PayloadLength(payloadLength)
	, HdrFragment(hdrFragment)
	, Protocol (protocol)
{
}
