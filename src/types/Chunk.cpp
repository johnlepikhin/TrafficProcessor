
#include "Chunk.h"
#include "../core/ParsersCollection.h"

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

Processor::Processor ()
	: Followers(new std::vector<Processor>())
{
}

Processor::~Processor()
{
	if (Followers)
		try {
			delete Followers;
		} catch (...) {

		}
}

Chunk *Processor::DoParse(Data *data, Chunk *parent)
{
	return (0);
}

std::string Processor::ID () {
	return ("");
}

std::string Processor::Description () {
	return ("");
}


std::vector<Processor> *Processor::GetFollowers ()
{
	return (Followers);
}

void Processor::SetFollowers(std::vector<Processor> *followers)
{
	delete Followers;
	Followers = followers;
}
