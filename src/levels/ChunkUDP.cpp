
#include "ChunkUDP.h"

ChunkUDP::ChunkUDP(BaseQuilt baseData
		, PayloadQuilt payload
		, std::shared_ptr<PacketIPTraits> parent
		, const unsigned int pktLength
		, const unsigned int payloadLength
		, const unsigned int sourcePort
		, const unsigned int destinationPort)
	: Chunk<PacketIPTraits>(baseData, payload, parent)
	, PktLength(pktLength)
	, PayloadLength(payloadLength)
	, SourcePort(sourcePort)
	, DestinationPort(destinationPort)
{

}
