// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "ParserTCP.h"
#include "ChunkTCP.h"
#include "PacketIPv4.h"

std::string ParserTCP::ID()
{
	return (std::string("TCP_Fragment"));
}

std::string ParserTCP::Description()
{
	return (std::string("TCP fragment"));
}

std::shared_ptr<ChunkTCP> ParserTCP::Process(const std::shared_ptr<PacketIPVariant> &packet)
{
	int Protocol = -1;
	unsigned short pktLength;
	PayloadQuilt Payload;
	BaseQuilt BaseData;
	if (packet->IPv4 != nullptr) {
		PacketIPv4 *ipv4 = packet->IPv4.get();
		Protocol = ipv4->Parent->Protocol;
		pktLength = ipv4->ExpectedSize;
		Payload = ipv4->Payload;
		BaseData = ipv4->BaseData;
	} else if (packet->IPv6 != nullptr) {
		// TODO
//		Protocol = packet->IPv6->Parent->Protocol;
//		pktLength = packet->IPv6->ExpectedSize;
//		Payload = packet->IPv6->Payload;
//		BaseData = packet->IPv6->BaseData;
	}

	if (6 == Protocol) {
		unsigned int sourcePort = Payload->GetShortBEOrFail(0);

		unsigned short destinationPort = Payload->GetShortBEOrFail(2);

		uint32_t seqNumber(0);
		Payload->CopyBytesOrFail(reinterpret_cast<char *>(&seqNumber) //-V206
				, 4, 4); //-V112

		uint32_t confirmNumber(0);
		Payload->CopyBytesOrFail(reinterpret_cast<char *>(&confirmNumber) //-V206
				, 8, 4); //-V112

		uint16_t headerLength = (Payload->GetCharOrFail(12) >> 4) << 2;

		unsigned char flags = Payload->GetCharOrFail(13) & 0b111111;

		uint16_t windowSize = Payload->GetShortBEOrFail(15);

		PayloadQuilt payload = std::make_shared<CPayloadQuilt>(Payload, headerLength);

		std::shared_ptr<ChunkTCP> r = std::make_shared<ChunkTCP>(BaseData
				, payload
				, packet
				, pktLength
				, headerLength
				, pktLength-headerLength
				, flags
				, windowSize
				, seqNumber
				, confirmNumber
				, sourcePort
				, destinationPort
		);

		return (r);
	}

	return (std::shared_ptr<ChunkTCP>(nullptr));
}
