
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

std::shared_ptr<ChunkTCP> ParserTCP::Process(std::shared_ptr<PacketIPTraits> packet)
{
	if (6 == packet->IPChunk->Protocol) {
		unsigned short pktLength = packet->ExpectedSize;

		unsigned int sourcePort = packet->IPPayload->GetShortBEOrFail(0);

		unsigned short destinationPort = packet->IPPayload->GetShortBEOrFail(2);

		unsigned long seqNumber(0);
		packet->IPPayload->CopyBytesOrFail((char *)&seqNumber, 4, 4);

		unsigned long confirmNumber(0);
		packet->IPPayload->CopyBytesOrFail((char *)&confirmNumber, 8, 4);

		unsigned short headerLength = (packet->IPPayload->GetCharOrFail(12) >> 4) << 2;

		unsigned char flags = packet->IPPayload->GetCharOrFail(13) & 0b111111;

		unsigned short windowSize = packet->IPPayload->GetShortBEOrFail(15);

		PayloadQuilt payload(new CPayloadQuilt(packet->IPPayload, headerLength));

		std::shared_ptr<ChunkTCP> r(new ChunkTCP(packet->IPBaseData
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
