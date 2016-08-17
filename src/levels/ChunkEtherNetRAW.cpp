
#include "ChunkEtherNetRAW.h"

ChunkEtherNetRAW::ChunkEtherNetRAW(Data *data
		, const unsigned long dataPosition
		, ChunkEtherNet *parent
		, const unsigned short length)
	: Chunk(data, dataPosition, parent)
	, PayloadLength(length)

{
}
