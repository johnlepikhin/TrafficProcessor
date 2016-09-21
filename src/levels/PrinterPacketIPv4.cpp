
#include "PrinterPacketIPv4.h"

std::string PrinterPacketIPv4::ID()
{
	return (std::string("IPv4Packet_Printer"));
}

std::string PrinterPacketIPv4::Description()
{
	return (std::string("IPv4 packet printer"));
}

Chunk *PrinterPacketIPv4::Process(Quilt *data, Chunk *p)
{
	PacketIPv4 *parent = dynamic_cast<PacketIPv4 *>(p);

	if (parent && parent->IsComplete) {
		ChunkIPv4 *hdr = (ChunkIPv4 *)parent->Parent;
		std::cout << "IPv4_Packet " << IPv4Addr::asString(hdr->SrcIP)
				<< " " << IPv4Addr::asString(hdr->DstIP)
				<< " ID=" << hdr->ID
				<< " Protocol=" << (int)hdr->Protocol
				<< " packetLength=" << parent->ExpectedSize
				<< " dataLength=" << parent->ReceivedSize
				<< " isComplete=" << parent->IsComplete
				<< "\n";
	}
	return (0);
}
