
#include "ChunkEtherNetRAW.h"

ChunkEtherNetRAW::ChunkEtherNetRAW(Quilt *data
		, Quilt *containedData
		, ChunkEtherNet *parent
		, const unsigned short length)
	: Chunk(data, containedData, parent)
	, PayloadLength(length)

{
}
