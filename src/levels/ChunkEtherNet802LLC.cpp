
#include "ChunkEtherNet802LLC.h"

ChunkEtherNet802LLC::ChunkEtherNet802LLC(const Quilt *data
		, const Quilt *containedData
		, const ChunkEtherNet *parent
		, const unsigned short length
		, const unsigned char dsap
		, const unsigned char ssap
		, const unsigned char control)
	: Chunk(data, containedData, parent)
	, PayloadLength(length)
	, DSAP(dsap)
	, SSAP(ssap)
	, Control(control)
{
}
