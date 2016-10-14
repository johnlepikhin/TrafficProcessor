
#include "ParserUDP.h"

std::string ParserUDP::ID()
{
	return (std::string("UDP_Packet"));
}

std::string ParserUDP::Description()
{
	return (std::string("UDP packet"));
}

std::shared_ptr<ChunkUDP> ParserUDP::Process(std::shared_ptr<PacketIPVariant> packet)
{
	int Protocol = -1;
	PayloadQuilt Payload;
	BaseQuilt BaseData;
	if (packet->IPv4 != nullptr) {
		Protocol = packet->IPv4->Parent->Protocol;
		Payload = packet->IPv4->Payload;
		BaseData = packet->IPv4->BaseData;
	} else if (packet->IPv6 != nullptr) {
		// TODO
//		Protocol = packet->IPv6->Parent->Protocol;
//		pktLength = packet->IPv6->ExpectedSize;
//		Payload = packet->IPv6->Payload;
//		BaseData = packet->IPv6->BaseData;
	}

	if (17 == Protocol) {
		unsigned int sourcePort = Payload->GetShortBEOrFail(0);

		unsigned short destinationPort = Payload->GetShortBEOrFail(2);

		unsigned short pktLength = Payload->GetShortBEOrFail(4);

		PayloadQuilt payload(new CPayloadQuilt(Payload, 8));

		std::shared_ptr<ChunkUDP> r(new ChunkUDP(BaseData
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
