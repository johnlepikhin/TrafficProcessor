
#include "Chunk.h"

Chunk::Chunk(Data *data, Chunk *parent)
	: DataPtr(data)
	, DataPosition(data->Position)
	, Parent(parent)
{
}

Chunk::Chunk(Data *data)
: DataPtr(data)
, DataPosition(data->Position)
, Parent(NULL)
{
}
