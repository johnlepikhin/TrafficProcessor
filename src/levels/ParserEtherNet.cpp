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

std::string ParserEtherNet::ID()
{
	return (std::string("Ethernet"));
}

std::string ParserEtherNet::Description()
{
	return (std::string("Ethernet frame"));
}

ChunkEtherNet *ParserEtherNet::Process(Quilt *data, Chunk *parent)
{
	const MAC *DA = new MAC(*data, 0);
	const MAC *SA = new MAC(*data, 6);

	unsigned short eType = data->GetShortBEOrFail(12);
	Quilt *containedData = new QuiltCut(data, 14);
	ChunkEtherNet *r = new ChunkEtherNet(data, containedData, DA, SA, eType);

	return (r);
}
