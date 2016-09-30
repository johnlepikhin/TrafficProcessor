
#include "ChunkEtherNetDIX.h"

ChunkEtherNetDIX::ChunkEtherNetDIX(BaseQuilt baseData
		, PayloadQuilt payload
		, std::shared_ptr<ChunkEtherNet> parent
		, const unsigned short etherType)
	: Chunk<ChunkEtherNet>(baseData, payload, parent)
	, EtherNetType(etherType)

{
}
