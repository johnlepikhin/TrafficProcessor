
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
	std::cout << "IPv6 " << srcIP
		<< " " << dstIP
		<< " flowLabel=" << (unsigned long)ipv6->FlowLabel
		<< " hopLimit=" << (unsigned long)ipv6->HopLimit
		<< " payloadLength=" << (unsigned long)ipv6->PayloadLength
		<< " protocol=" << (unsigned long)ipv6->Protocol
		<< " trafficClass=" << (unsigned long)ipv6->TrafficClass
		<< " fragment_offset=" << (unsigned long)ipv6->HdrFragment->FragmentOffset
		<< " fragment_has_next=" << (unsigned long)ipv6->HdrFragment->HasNextFragments
		<< " fragment_packet_id=" << (unsigned long)ipv6->HdrFragment->PacketID
		<< "\n";

	return (std::shared_ptr<ChunkRaw>(nullptr));
}
