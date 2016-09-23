
#include "ChunkTCP.h"

ChunkTCP::ChunkTCP(Quilt *data
		, Quilt *containedData
		, const unsigned int pktLength
		, const unsigned int headerLength
		, const unsigned int payloadLength
		, const unsigned char flags
		, const unsigned short windowSize
		, const unsigned short seqNumber
		, const unsigned short confirmNumber
		, const unsigned int sourcePort
		, const unsigned int destinationPort)
	: Chunk(data, containedData)
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
