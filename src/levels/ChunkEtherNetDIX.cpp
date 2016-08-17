
#include "ChunkEtherNetDIX.h"

ChunkEtherNetDIX::ChunkEtherNetDIX(Data *data
		, const unsigned long dataPosition
		, ChunkEtherNet *parent
		, const unsigned short etherType)
	: Chunk(data, dataPosition, parent)
	, EtherNetType(etherType)

{
}
