
#include "Chunk.h"
#include "../core/ProcessorsCollection.h"

Chunk::Chunk(const Quilt *data, const Quilt *containedData, const Chunk *parent)
	: Data(data)
	, ContainedData(containedData)
	, Parent(parent)
{
}

Chunk::Chunk(const Quilt *data, const Quilt *containedData)
	: Data(data)
	, ContainedData(containedData)
	, Parent(NULL)
{
}

Chunk::~Chunk()
{
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

void Processor::Recursive(const Quilt *data, const Chunk *parent)
{
	Chunk *result = this->Process(data, parent);
	if (NULL != result) {
		try {
			for (std::vector<Processor *>::iterator i = Followers.begin(); i != Followers.end(); ++i) {
				(*i)->Recursive(result->ContainedData, result);
			}
		} catch (...) {
			delete result;
			throw;
		}
		delete result;
	}
}

std::string Processor::ID () {
	return ("");
}

std::string Processor::Description () {
	return ("");
}


const std::vector<Processor *> &Processor::GetFollowers () const
{
	return (Followers);
}

void Processor::AddFollower(Processor *follower)
{
	Followers.push_back(follower);
}

void Processor::SetFollowers(std::vector<Processor *> &followers)
{
	for (std::vector<Processor *>::iterator i = Followers.begin(); i != Followers.end(); ++i) {
		if ((*i) != NULL) {
			delete (*i);
		}
	}
	Followers.clear();
	for (std::vector<Processor *>::iterator i = followers.begin(); i != followers.end(); ++i) {
		Followers.push_back((*i));
	}
}
