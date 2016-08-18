/*
 * ParserEtherNet.cpp
 *
 *  Created on: 16 авг. 2016 г.
 *      Author: eugene
 */

#include "ParserEtherNet.h"
#include "ParserEtherNetDIX.h"
#include "ParserEtherNet802LLC.h"
#include "ParserEtherNetRAW.h"
#include "ParserEtherNetSNAP.h"

ParserEtherNet::ParserEtherNet()
{
	std::vector<Processor *> followers;
	followers.push_back(new ParserEtherNetDIX());
	followers.push_back(new ParserEtherNet802LLC());
	followers.push_back(new ParserEtherNetRAW());
	followers.push_back(new ParserEtherNetSNAP());
	SetFollowers(&followers);
}

std::string ParserEtherNet::ID()
{
	return (std::string("Ethernet"));
}

std::string ParserEtherNet::Description()
{
	return (std::string("Ethernet frame"));
}

ChunkEtherNet *ParserEtherNet::DoParse(Data *data, Chunk *parent)
{
	MAC *DA = new MAC(data);
	MAC *SA = new MAC(data);
	try {
		const unsigned long dataPosition = data->Position;
		unsigned short eType = data->read2Reverse();
		ChunkEtherNet *r = new ChunkEtherNet(data, dataPosition, DA, SA, eType);
		return (r);
	} catch (...) {
		delete DA;
		delete SA;
		throw;
	}
}
