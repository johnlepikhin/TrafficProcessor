
#include "PacketIPTraits.h"

PacketIPTraits::PacketIPTraits(bool isComplete
		, unsigned int rawIfaceLength
		, unsigned int expectedSize
		, std::shared_ptr<ChunkIPTraits> parent
		, PayloadQuilt payload
		, BaseQuilt baseData)
	: IsComplete(isComplete)
	, RawIfaceLength(rawIfaceLength)
	, ExpectedSize(expectedSize)
	, IPChunk(parent)
	, IPPayload(payload)
	, IPBaseData(baseData)
{
}
