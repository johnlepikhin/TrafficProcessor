
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

Chunk::~Chunk()
{
	Parent = 0;
	DataPtr = 0;
}

Processor::Processor ()
{
}

Processor::~Processor()
{
	try {
		for (std::vector<Processor *>::iterator i = Followers.begin(); i != Followers.end(); ++i) {
			delete (*i);
		}
		Followers.clear();
	} catch (...) {

	}
}

Chunk *Processor::Process(Data *data, Chunk *parent)
{
	return (0);
}

std::string Processor::ID () {
	return ("");
}

std::string Processor::Description () {
	return ("");
}


const std::vector<Processor *> *Processor::GetFollowers ()
{
	return (&Followers);
}

void Processor::SetFollowers(std::vector<Processor *> *followers)
{
	for (std::vector<Processor *>::iterator i = Followers.begin(); i != Followers.end(); ++i) {
		if ((*i) != NULL) {
			delete (*i);
		}
	}
	Followers.clear();
	for (std::vector<Processor *>::iterator i = followers->begin(); i != followers->end(); ++i) {
		Followers.push_back((*i));
	}
}
