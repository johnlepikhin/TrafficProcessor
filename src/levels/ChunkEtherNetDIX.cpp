
#include "ChunkEtherNetDIX.h"

ChunkEtherNetDIX::ChunkEtherNetDIX(BaseQuilt *baseData
		, PayloadQuilt *payload
		, ChunkEtherNet *parent
		, const unsigned short etherType)
	: Chunk<ChunkEtherNet>(baseData, payload, parent)
	, EtherNetType(etherType)

{
}
