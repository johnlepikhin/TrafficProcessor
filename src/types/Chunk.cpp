
#include "Chunk.h"

void ChunkTraits::IncrRefs(int incr)
{
	RefCounter+=incr;
}

int ChunkTraits::DecrRefs(int decr)
{
	RefCounter-=decr;
	return (RefCounter);
}
