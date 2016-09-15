
#include "ChunkEtherNetRAW.h"

ChunkEtherNetRAW::ChunkEtherNetRAW(const Quilt *data
		, const Quilt *containedData
		, const ChunkEtherNet *parent
		, const unsigned short length)
	: Chunk(data, containedData, parent)
	, PayloadLength(length)

{
}
