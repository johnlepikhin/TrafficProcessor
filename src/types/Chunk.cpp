
#include "Chunk.h"

Chunk::Chunk(const Data * const data, Chunk *parent)
	: DataPtr(data)
	, DataPosition(data->Position)
	, Parent(parent)
{
}

Chunk::Chunk(const Data *data)
	: DataPtr(data)
	, DataPosition(data->Position)
	, Parent(NULL)
{
}

template <class PARENT, class RETURN>
Parser<PARENT, RETURN>::Parser ()
	: Followers(std::vector<Parser<PARENT, RETURN> >())
{
}

template <class PARENT, class RETURN>
std::vector<Parser<PARENT, RETURN> > *Parser<PARENT, RETURN>::GetFollowers ()
{
	return (Followers);
}
