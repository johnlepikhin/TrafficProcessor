
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
}

PacketIPv4::~PacketIPv4()
{
}

bool PacketIPv4::AddChunk(ChunkIPv4 *chunk)
{
	QuiltSew *sew = (QuiltSew *)ContainedData;

	sew->SewWithHole(chunk->ContainedData, chunk->FragmentOffset, chunk->PktLength);

	if ( ! chunk->FlagIsFragmented) {
		if (0 == chunk->FragmentOffset) {
			IsComplete = true;
			ExpectedSize = chunk->PktLength;
			ReceivedSize = chunk->PktLength;
			return (true);
		} else {
			ExpectedSize = chunk->FragmentOffset + chunk->PktLength;
		}
	} else {
		ReceivedSize += chunk->PktLength;
	}

	if (ReceivedSize == ExpectedSize) {
		IsComplete = true;
	}

	return (IsComplete);
}
