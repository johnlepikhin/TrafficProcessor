// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "ChunkEtherNetDIX.h"

ChunkEtherNetDIX::ChunkEtherNetDIX(const BaseQuilt &baseData
		, const PayloadQuilt &payload
		, const std::shared_ptr<ChunkEtherNet> &parent
		, const unsigned short etherType)
	: Chunk<ChunkEtherNet>(baseData, payload, parent)
	, EtherNetType(etherType)

{
}
