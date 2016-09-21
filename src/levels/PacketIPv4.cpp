
#include "PacketIPv4.h"
#include <sparsed-ropes/Quilt.h>

#include "../types/Chunk.h"

PacketIPv4::PacketIPv4(ChunkIPv4 *chunk)
	: Chunk(NULL, new QuiltSew(), chunk)
	, IsComplete(false)
	, ReceivedSize(0)
	, ExpectedSize(0)
{
	AddChunk(chunk);
	chunk->IncrRefs(1);
}

PacketIPv4::~PacketIPv4()
{
	Parent->DecrRefs(1);
	if (!Parent->RefCounter) {
		delete Parent;
	}
}

bool PacketIPv4::AddChunk(ChunkIPv4 *chunk)
{
	QuiltSew *sew = (QuiltSew *)ContainedData;

	sew->SewWithHole(chunk->ContainedData, chunk->FragmentOffset, chunk->PayloadLength);

	if ( ! chunk->FlagIsFragmented) {
		if (0 == chunk->FragmentOffset) {
			IsComplete = true;
			ExpectedSize = chunk->PayloadLength;
			ReceivedSize = chunk->PayloadLength;
			return (true);
		} else {
			ExpectedSize = chunk->FragmentOffset + chunk->PayloadLength;
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
