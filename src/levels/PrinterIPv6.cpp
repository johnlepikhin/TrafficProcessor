// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "PrinterIPv6.h"

std::string PrinterIPv6::ID()
{
	return (std::string("IPv6_Printer"));
}

std::string PrinterIPv6::Description()
{
	return (std::string("IPv6 chunk printer"));
}

std::shared_ptr<ChunkRaw> PrinterIPv6::Process(std::shared_ptr<ChunkIPv6> ipv6)
{
	std::string srcIP = ipv6->SrcIP.AsString();
	std::string dstIP = ipv6->DstIP.AsString();
	IPv6HeaderFragment *hdrFragment = ipv6->HdrFragment.get();
	std::cout << "IPv6 " << srcIP
		<< " " << dstIP
		<< " flowLabel=" << static_cast<uint32_t>(ipv6->FlowLabel)
		<< " hopLimit=" << static_cast<uint32_t>(ipv6->HopLimit)
		<< " payloadLength=" << static_cast<uint32_t>(ipv6->PayloadLength)
		<< " protocol=" << static_cast<uint32_t>(ipv6->Protocol)
		<< " trafficClass=" << static_cast<uint32_t>(ipv6->TrafficClass)
		<< " fragment_offset=" << static_cast<uint32_t>(hdrFragment->FragmentOffset)
		<< " fragment_has_next=" << static_cast<uint32_t>(hdrFragment->HasNextFragments)
		<< " fragment_packet_id=" << static_cast<uint32_t>(hdrFragment->PacketID)
		<< "\n";

	return (std::shared_ptr<ChunkRaw>(nullptr));
}
