
#include "PrinterPacketIPv4.h"

std::string PrinterPacketIPv4::ID()
{
	return (std::string("IPv4Packet_Printer"));
}

std::string PrinterPacketIPv4::Description()
{
	return (std::string("IPv4 packet printer"));
}

ChunkRaw *PrinterPacketIPv4::Process(PacketIPv4 *packet)
{
	if (packet->IsComplete) {
		std::cout << "IPv4_Packet " << IPv4Addr::asString(packet->Parent->SrcIP)
				<< " " << IPv4Addr::asString(packet->Parent->DstIP)
				<< " ID=" << packet->Parent->ID
				<< " Protocol=" << (int)packet->Parent->Protocol
				<< " packetLength=" << packet->ExpectedSize
				<< " dataLength=" << packet->ReceivedSize
				<< " isComplete=" << packet->IsComplete
				<< "\n";
	}
	return (0);
}
