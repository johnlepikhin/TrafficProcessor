
#include "ChunkEtherNet802LLC.h"

ChunkEtherNet802LLC::ChunkEtherNet802LLC(BaseQuilt baseData
		, PayloadQuilt payload
		, std::shared_ptr<ChunkEtherNet> parent
		, const unsigned short length
		, const unsigned char dsap
		, const unsigned char ssap
		, const unsigned char control)
	: Chunk<ChunkEtherNet>(baseData, payload, parent)
	, PayloadLength(length)
	, DSAP(dsap)
	, SSAP(ssap)
	, Control(control)
{
}
