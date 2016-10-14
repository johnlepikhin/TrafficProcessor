
#include "ChunkTCP.h"

ChunkTCP::ChunkTCP(BaseQuilt baseData
		, PayloadQuilt payload
		, std::shared_ptr<PacketIPVariant> parent
		, const unsigned int pktLength
		, const unsigned int headerLength
		, const unsigned int payloadLength
		, const unsigned char flags
		, const unsigned short windowSize
		, const unsigned long seqNumber
		, const unsigned long confirmNumber
		, const unsigned int sourcePort
		, const unsigned int destinationPort)
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
