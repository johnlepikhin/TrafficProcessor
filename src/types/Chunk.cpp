
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

Parser::Parser ()
	: Followers(new std::vector<Parser>())
{
}

Parser::~Parser()
{
	if (Followers)
		try {
			delete Followers;
		} catch (...) {

		}
}

Chunk *Parser::DoParse(Data *data, Chunk *parent)
{
	return (0);
}

std::string Parser::ID () {
	return ("");
}

std::string Parser::Description () {
	return ("");
}


std::vector<Parser> *Parser::GetFollowers ()
{
	return (Followers);
}

void Parser::SetFollowers(std::vector<Parser> *followers)
{
	delete Followers;
	Followers = followers;
}
