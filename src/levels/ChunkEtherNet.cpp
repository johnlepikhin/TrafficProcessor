/*
 * ChunkEtherNet.cpp
 *
 *  Created on: 15 авг. 2016 г.
 *      Author: eugene
 */

#include "ChunkEtherNet.h"

ChunkEtherNet::ChunkEtherNet(Data *data,
		const MAC * const destinationMAC,
		const MAC * const sourceMAC,
		const unsigned short ethernetType)
	: Chunk(data)
	, DestinationMAC(destinationMAC)
	, SourceMAC(sourceMAC)
	, EtherNetType(ethernetType)
{
}

ChunkEtherNet::~ChunkEtherNet()
{
	delete SourceMAC;
	delete DestinationMAC;
}
