
#include "ChunkEtherNetRAW.h"

ChunkEtherNetRAW::ChunkEtherNetRAW(Quilt *data
		, Quilt *containedData
		, const ChunkEtherNet *parent
		, const unsigned short length)
	: Chunk(data, containedData, parent)
	, PayloadLength(length)

{
}
