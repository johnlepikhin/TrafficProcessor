
#include "ChunkTCP.h"

ChunkTCP::ChunkTCP(BaseQuilt baseData
		, PayloadQuilt payload
		, std::shared_ptr<PacketIPVariant> parent
		, const uint16_t pktLength
		, const uint16_t headerLength
		, const uint16_t payloadLength
		, const uint8_t flags
		, const uint16_t windowSize
		, const uint32_t seqNumber
		, const uint32_t confirmNumber
		, const uint16_t sourcePort
		, const uint16_t destinationPort)
	: Chunk<PacketIPVariant>(baseData, payload, parent)
	, PktLength(pktLength)
	, HeaderLength(headerLength)
	, PayloadLength(payloadLength)
	, SourcePort(sourcePort)
	, DestinationPort(destinationPort)
	, FlagURG(flags & 0x20)
	, FlagACK(flags & 0x10)
	, FlagPSH(flags & 8)
	, FlagRST(flags & 4)
	, FlagSYN(flags & 2)
	, FlagFIN(flags & 1)
	, WindowSize(windowSize)
	, SeqNumber(seqNumber)
	, ConfirmNumber(confirmNumber)
{

}
