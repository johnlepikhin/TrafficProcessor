// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "ChunkEtherNet802LLC.h"

ChunkEtherNet802LLC::ChunkEtherNet802LLC(const BaseQuilt &baseData
		, const PayloadQuilt &payload
		, const std::shared_ptr<ChunkEtherNet> &parent
		, const unsigned short length
		, const unsigned char dsap
		, const unsigned char ssap
		, const unsigned char control)
	: Chunk<ChunkEtherNet>(baseData, payload, parent)
	, PayloadLength(length)
	, DSAP(dsap)
	, SSAP(ssap)
	, Control(control)
{
}
