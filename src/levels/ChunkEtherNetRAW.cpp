// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "ChunkEtherNetRAW.h"

ChunkEtherNetRAW::ChunkEtherNetRAW(const BaseQuilt &baseData
		, const PayloadQuilt &payload
		, const std::shared_ptr<ChunkEtherNet> &parent
		, const unsigned short length)
	: ChunkEtherNetTraits(baseData, payload, parent)
	, PayloadLength(length)

{
}
