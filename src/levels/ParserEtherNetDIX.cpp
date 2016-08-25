/*
 * ParseEtherNetDIX.cpp
 *
 *  Created on: 16 авг. 2016 г.
 *      Author: eugene
 */

#include <typeinfo>

#include "ParserEtherNetDIX.h"
#include "ParserIPv4.h"
#include "ParserIPv6.h"

ParserEtherNetDIX::ParserEtherNetDIX()
{
	std::vector<Processor *> followers;
	followers.push_back(new ParserIPv4());
	followers.push_back(new ParserIPv6());
	SetFollowers(&followers);
}


std::string ParserEtherNetDIX::ID()
{
	return (std::string("EthernetDIX"));
}

std::string ParserEtherNetDIX::Description()
{
	return (std::string("Ethernet DIX frame"));
}

ChunkEtherNetDIX *ParserEtherNetDIX::Process(Data *data, Chunk *p)
{
	const unsigned long dataPosition = data->Position;

	ChunkEtherNet *parent = (ChunkEtherNet *)p;

	if (parent->EtherNetType > 1500) {
		return (new ChunkEtherNetDIX(data, dataPosition, parent, parent->EtherNetType));
	}

	return (NULL);
}
