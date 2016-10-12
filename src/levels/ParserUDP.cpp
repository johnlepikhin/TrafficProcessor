
#include "ParserUDP.h"

std::string ParserUDP::ID()
{
	return (std::string("UDP_Packet"));
}

std::string ParserUDP::Description()
{
	return (std::string("UDP packet"));
}

std::shared_ptr<ChunkUDP> ParserUDP::Process(std::shared_ptr<PacketIPTraits> packet)
{
	if (17 == packet->IPChunk->Protocol) {
		unsigned int sourcePort = packet->IPPayload->GetShortBEOrFail(0);

		unsigned short destinationPort = packet->IPPayload->GetShortBEOrFail(2);

		unsigned short pktLength = packet->IPPayload->GetShortBEOrFail(4);

		PayloadQuilt payload(new CPayloadQuilt(packet->IPPayload, 8));

		std::shared_ptr<ChunkUDP> r(new ChunkUDP(packet->IPBaseData
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
