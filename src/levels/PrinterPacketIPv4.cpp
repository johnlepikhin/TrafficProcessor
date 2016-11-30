// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "PrinterPacketIPv4.h"

std::string PrinterPacketIPv4::ID()
{
	return (std::string("IPv4Packet_Printer"));
}

std::string PrinterPacketIPv4::Description()
{
	return (std::string("IPv4 packet printer"));
}

std::shared_ptr<ChunkRaw> PrinterPacketIPv4::Process(std::shared_ptr<PacketIPv4> packet)
{
	if (packet->IsComplete) {
		std::cout << "IPv4_Packet " << IPv4Addr::asString(packet->Parent->SrcIP)
				<< " " << IPv4Addr::asString(packet->Parent->DstIP)
				<< " ID=" << packet->Parent->ID
				<< " Protocol=" << (int)packet->Parent->Protocol
				<< " packetLength=" << packet->ExpectedSize
				<< " dataLength=" << packet->ReceivedSize
				<< " ifaceLength=" << packet->RawIfaceLength
				<< " isComplete=" << packet->IsComplete
				<< "\n";
	}

	return (std::shared_ptr<ChunkRaw>(nullptr));
}
