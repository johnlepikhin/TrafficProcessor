
#include "ChunkTCP.h"

ChunkTCP::ChunkTCP(Quilt *data
		, Quilt *containedData
		, const unsigned int pktLength
		, const unsigned int headerLength
		, const unsigned int payloadLength
		, const unsigned int sourcePort
		, const unsigned int destinationPort)
	: Chunk(data, containedData)
	, PktLength(pktLength)
	, HeaderLength(headerLength)
	, PayloadLength(payloadLength)
	, SourcePort(sourcePort)
	, DestinationPort(destinationPort)
{

}
