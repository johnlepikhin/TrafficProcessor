
#include "PacketIPv4.h"
#include <sparsed-ropes/Quilt.h>

#include "../types/Chunk.h"

PacketIPv4::PacketIPv4(BaseQuilt baseData
		, PayloadQuilt payload
		, std::shared_ptr<ChunkIPv4> parent)
	: Chunk(baseData, payload, parent)
	, IsComplete(false)
	, ReceivedSize(0)
	, RawIfaceLength(0)
	, ExpectedSize(0)
{
	AddChunk(parent);
}

bool PacketIPv4::AddChunk(std::shared_ptr<ChunkIPv4> chunk)
{
	Payload->SewWithHole(chunk->Payload, chunk->FragmentOffset, chunk->PayloadLength);
	RawIfaceLength += chunk->BaseData->Length;

	if ( ! chunk->FlagIsFragmented) {
		if (0 == chunk->FragmentOffset) {
			IsComplete = true;
			ExpectedSize = chunk->PayloadLength;
			ReceivedSize = chunk->PayloadLength;
			return (true);
		} else {
			uint16_t tmp = chunk->FragmentOffset + chunk->PayloadLength;
			ExpectedSize = (ExpectedSize > tmp) ? ExpectedSize : tmp;
			ReceivedSize += chunk->PayloadLength;
		}
	} else {
		ReceivedSize += chunk->PayloadLength;
	}

	if (ReceivedSize == ExpectedSize) {
		IsComplete = true;
	}

	return (IsComplete);
}
