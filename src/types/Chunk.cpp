
#include "Chunk.h"
#include "../core/ProcessorsCollection.h"

Chunk::Chunk(Quilt *data, Quilt *containedData, Chunk *parent)
	: Data(data)
	, ContainedData(containedData)
	, Parent(parent)
	, RefCounter(0)
{
}

Chunk::Chunk(Quilt *data, Quilt *containedData)
	: Data(data)
	, ContainedData(containedData)
	, Parent(NULL)
	, RefCounter(0)
{
}

Chunk::~Chunk()
{
	if (ContainedData)
		delete ContainedData;
}

void Chunk::IncrRefs(int incr)
{
	RefCounter+=incr;
}

int Chunk::DecrRefs(int decr)
{
	RefCounter-=decr;
	return (RefCounter);
}

Processor::Processor ()
{
}

void Processor::DestroyChunk(Chunk *chunk)
{
	delete chunk;
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

void Processor::Recursive(Quilt *data, Chunk *parent)
{
	Chunk *result = this->Process(data, parent);
	if (NULL != result) {
		try {
			for (std::vector<Processor *>::iterator i = Followers.begin(); i != Followers.end(); ++i) {
				(*i)->Recursive(result->ContainedData, result);
			}
		} catch (...) {
			DestroyChunk(result);
			throw;
		}
		if (!result->RefCounter)
			DestroyChunk(result);
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
