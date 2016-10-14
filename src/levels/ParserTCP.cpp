
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

std::shared_ptr<ChunkTCP> ParserTCP::Process(std::shared_ptr<PacketIPVariant> packet)
{
	int Protocol = -1;
	unsigned short pktLength;
	PayloadQuilt Payload;
	BaseQuilt BaseData;
	if (packet->IPv4 != nullptr) {
		Protocol = packet->IPv4->Parent->Protocol;
		pktLength = packet->IPv4->ExpectedSize;
		Payload = packet->IPv4->Payload;
		BaseData = packet->IPv4->BaseData;
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

		unsigned long seqNumber(0);
		Payload->CopyBytesOrFail((char *)&seqNumber, 4, 4);

		unsigned long confirmNumber(0);
		Payload->CopyBytesOrFail((char *)&confirmNumber, 8, 4);

		unsigned short headerLength = (Payload->GetCharOrFail(12) >> 4) << 2;

		unsigned char flags = Payload->GetCharOrFail(13) & 0b111111;

		unsigned short windowSize = Payload->GetShortBEOrFail(15);

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
