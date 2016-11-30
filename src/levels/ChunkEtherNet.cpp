// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "ChunkEtherNet.h"

ChunkEtherNet::ChunkEtherNet(const BaseQuilt &baseData
		, const PayloadQuilt &payload
		, const unsigned long long destinationMAC
		, const unsigned long long sourceMAC
		, const unsigned short ethernetType)
	: Chunk<CBaseQuilt>(baseData, payload)
	, DestinationMAC(destinationMAC)
	, SourceMAC(sourceMAC)
	, EtherNetType(ethernetType)
{
}
