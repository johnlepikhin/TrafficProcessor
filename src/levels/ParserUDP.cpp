
#include "ParserUDP.h"

std::string ParserUDP::ID()
{
	return (std::string("UDP_Packet"));
}

std::string ParserUDP::Description()
{
	return (std::string("UDP packet"));
}

std::shared_ptr<ChunkUDP> ParserUDP::Process(std::shared_ptr<PacketIPv4> packet)
{
	if (17 == packet->Parent->Protocol) {
		unsigned int sourcePort = packet->Payload->GetShortBEOrFail(0);

		unsigned short destinationPort = packet->Payload->GetShortBEOrFail(2);

		unsigned short pktLength = packet->Payload->GetShortBEOrFail(4);

		PayloadQuilt payload(new CPayloadQuilt(packet->Payload, 8));

		std::shared_ptr<ChunkUDP> r(new ChunkUDP(packet->BaseData
				, payload
				, packet
				, pktLength
				, pktLength-8
				, sourcePort
				, destinationPort
		));

		return (r);
	}

	return (std::shared_ptr<ChunkUDP>(nullptr));
}
