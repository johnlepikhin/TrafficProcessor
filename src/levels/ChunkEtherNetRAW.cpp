
#include "ChunkEtherNetRAW.h"

ChunkEtherNetRAW::ChunkEtherNetRAW(BaseQuilt *baseData
		, PayloadQuilt *payload
		, ChunkEtherNet *parent
		, const unsigned short length)
	: Chunk<ChunkEtherNet>(baseData, payload, parent)
	, PayloadLength(length)

{
}
