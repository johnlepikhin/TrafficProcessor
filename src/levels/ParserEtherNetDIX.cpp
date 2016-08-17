/*
 * ParseEtherNetDIX.cpp
 *
 *  Created on: 16 авг. 2016 г.
 *      Author: eugene
 */

#include <typeinfo>

#include "ParserEtherNetDIX.h"

std::string ParserEtherNetDIX::ID()
{
	return (std::string("EthernetDIX"));
}

std::string ParserEtherNetDIX::Description()
{
	return (std::string("Ethernet DIX frame"));
}

ChunkEtherNetDIX *ParserEtherNetDIX::DoParse(Data *data, Chunk *parent)
{
	const unsigned long dataPosition = data->Position;

	if (typeid(parent) != typeid(ChunkEtherNet)) {
		return (NULL);
	}

	ChunkEtherNet *ethernet = (ChunkEtherNet *)parent;

	if (ethernet->EtherNetType > 1500) {
		return (new ChunkEtherNetDIX(data, dataPosition, ethernet));
	}

	return (NULL);
}
