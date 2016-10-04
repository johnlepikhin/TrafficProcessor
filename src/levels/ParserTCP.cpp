
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

std::shared_ptr<ChunkTCP> ParserTCP::Process(std::shared_ptr<PacketIPv4> packet)
{
	if (6 == packet->Parent->Protocol) {
		unsigned short pktLength = packet->ExpectedSize;

		unsigned int sourcePort = packet->Payload->GetShortBEOrFail(0);

		unsigned short destinationPort = packet->Payload->GetShortBEOrFail(2);

		unsigned short seqNumber(0);
		packet->Payload->CopyBytesOrFail((char *)&seqNumber, 4, 4);

		unsigned short confirmNumber(0);
		packet->Payload->CopyBytesOrFail((char *)&confirmNumber, 8, 4);

		unsigned short headerLength = (packet->Payload->GetCharOrFail(12) >> 4) << 2;

		unsigned char flags = packet->Payload->GetCharOrFail(14);

		unsigned short windowSize = packet->Payload->GetShortBEOrFail(15);

		PayloadQuilt payload(new CPayloadQuilt(packet->Payload, headerLength));

		std::shared_ptr<ChunkTCP> r(new ChunkTCP(packet->BaseData
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
		));

		return (r);
	}

	return (std::shared_ptr<ChunkTCP>(nullptr));
}
