
#include "Chunk.h"
#include "../core/ProcessorsCollection.h"

Chunk::Chunk(const Data * const data, const unsigned long dataPosition, Chunk *parent)
	: DataPtr(data)
	, DataPosition(dataPosition)
	, Parent(parent)
{
}

Chunk::Chunk(const Data *data, const unsigned long dataPosition)
	: DataPtr(data)
	, DataPosition(dataPosition)
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
