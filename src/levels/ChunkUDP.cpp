
#include "ChunkUDP.h"

ChunkUDP::ChunkUDP(BaseQuilt baseData
		, PayloadQuilt payload
		, std::shared_ptr<PacketIPVariant> parent
		, const unsigned int pktLength
		, const unsigned int payloadLength
		, const unsigned int sourcePort
		, const unsigned int destinationPort)
	: Chunk<PacketIPVariant>(baseData, payload, parent)
	, PktLength(pktLength)
	, PayloadLength(payloadLength)
	, SourcePort(sourcePort)
	, DestinationPort(destinationPort)
{

}
