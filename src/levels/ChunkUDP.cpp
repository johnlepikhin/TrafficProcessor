// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "ChunkUDP.h"

ChunkUDP::ChunkUDP(const BaseQuilt &baseData
		, const PayloadQuilt &payload
		, const std::shared_ptr<PacketIPVariant> &parent
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
