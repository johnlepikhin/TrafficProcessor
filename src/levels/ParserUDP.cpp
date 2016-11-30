// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "ParserUDP.h"

std::string ParserUDP::ID()
{
	return (std::string("UDP_Packet"));
}

std::string ParserUDP::Description()
{
	return (std::string("UDP packet"));
}

std::shared_ptr<ChunkUDP> ParserUDP::Process(const std::shared_ptr<PacketIPVariant> &packet)
{
	int Protocol = -1;
	PayloadQuilt Payload;
	BaseQuilt BaseData;
	if (packet->IPv4 != nullptr) {
		PacketIPv4 *ipv4 = packet->IPv4.get();
		Protocol = ipv4->Parent->Protocol;
		Payload = ipv4->Payload;
		BaseData = ipv4->BaseData;
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

		uint16_t pktLength = Payload->GetShortBEOrFail(4); //-V112

		PayloadQuilt payload = std::make_shared<CPayloadQuilt>(Payload, 8);

		std::shared_ptr<ChunkUDP> r = std::make_shared<ChunkUDP>(BaseData
				, payload
				, packet
				, pktLength
				, pktLength-8
				, sourcePort
				, destinationPort
		);

		return (r);
	}

	return (std::shared_ptr<ChunkUDP>(nullptr));
}
