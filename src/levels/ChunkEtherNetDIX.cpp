
#include "ChunkEtherNetDIX.h"

ChunkEtherNetDIX::ChunkEtherNetDIX(const Quilt *data
		, const Quilt *containedData
		, const ChunkEtherNet *parent
		, const unsigned short etherType)
	: Chunk(data, containedData, parent)
	, EtherNetType(etherType)

{
}
