/*
 * ParserEtherNet.cpp
 *
 *  Created on: 16 авг. 2016 г.
 *      Author: eugene
 */

#include "ParserEtherNet.h"

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
		std::cout << "ether 1\n";
		const unsigned long dataPosition = data->Position;
		std::cout << "ether 2\n";
		unsigned short eType = data->read2Reverse();
		std::cout << "ether 3\n";
		ChunkEtherNet *r = new ChunkEtherNet(data, dataPosition, DA, SA, eType);
		std::cout << "ether 4\n";
		return (r);
	} catch (...) {
		delete DA;
		delete SA;
		throw;
	}
}
