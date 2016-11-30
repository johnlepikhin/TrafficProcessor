// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "PrinterIPv4.h"

std::string PrinterIPv4::ID()
{
	return (std::string("IPv4_Printer"));
}

std::string PrinterIPv4::Description()
{
	return (std::string("IPv4 chunk printer"));
}

std::shared_ptr<ChunkRaw> PrinterIPv4::Process(const std::shared_ptr<ChunkIPv4> &ipv4)
{
	std::string srcIP = IPv4Addr::asString(ipv4->SrcIP);
	std::string dstIP = IPv4Addr::asString(ipv4->DstIP);
	std::cout << "IPv4 " << srcIP
		<< " " << dstIP
		<< " packetLength=" << ipv4->PktLength
		<< " dontFragment=" << ipv4->FlagDontFragment
		<< " isFragmented=" << ipv4->FlagIsFragmented
		<< " ID=" << ipv4->ID
		<< " fragmentOffset=" << ipv4->FragmentOffset
		<< " TTL=" << ipv4->TTL
		<< "\n";

	return (std::shared_ptr<ChunkRaw>(nullptr));
}
