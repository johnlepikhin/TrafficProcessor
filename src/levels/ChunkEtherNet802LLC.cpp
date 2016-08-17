
#include "ChunkEtherNet802LLC.h"

ChunkEtherNet802LLC::ChunkEtherNet802LLC(Data *data
		, const unsigned long dataPosition
		, ChunkEtherNet *parent
		, const unsigned short length
		, const unsigned char dsap
		, const unsigned char ssap
		, const unsigned char control)
	: Chunk(data, dataPosition, parent)
	, PayloadLength(length)
	, DSAP(dsap)
	, SSAP(ssap)
	, Control(control)
{
}
