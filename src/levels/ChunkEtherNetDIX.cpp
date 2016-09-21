
#include "ChunkEtherNetDIX.h"

ChunkEtherNetDIX::ChunkEtherNetDIX(Quilt *data
		, Quilt *containedData
		, ChunkEtherNet *parent
		, const unsigned short etherType)
	: Chunk(data, containedData, parent)
	, EtherNetType(etherType)

{
}
