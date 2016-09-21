
#include "PrinterIPv4.h"

std::string PrinterIPv4::ID()
{
	return (std::string("IPv4_Printer"));
}

std::string PrinterIPv4::Description()
{
	return (std::string("IPv4 chunk printer"));
}

ChunkIPv4 *PrinterIPv4::Process(Quilt *data, Chunk *p)
{
	ChunkIPv4 *parent = dynamic_cast<ChunkIPv4 *>(p);

	if (parent) {
		std::cout << "IPv4 " << IPv4Addr::asString(parent->SrcIP)
				<< " " << IPv4Addr::asString(parent->DstIP)
				<< " packetLength=" << parent->PktLength
				<< " dontFragment=" << parent->FlagDontFragment
				<< " isFragmented=" << parent->FlagIsFragmented
				<< " ID=" << parent->ID
				<< " fragmentOffset=" << parent->FragmentOffset
				<< " TTL=" << parent->TTL
				<< "\n";
	}
	return (0);
}
