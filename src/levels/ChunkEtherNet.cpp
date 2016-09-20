/*
 * ChunkEtherNet.cpp
 *
 *  Created on: 15 авг. 2016 г.
 *      Author: eugene
 */

#include "ChunkEtherNet.h"

ChunkEtherNet::ChunkEtherNet(Quilt *data,
		Quilt *containedData,
		const MAC *destinationMAC,
		const MAC *sourceMAC,
		const unsigned short ethernetType)
	: Chunk(data, containedData)
	, DestinationMAC(destinationMAC)
	, SourceMAC(sourceMAC)
	, EtherNetType(ethernetType)
{
}

ChunkEtherNet::~ChunkEtherNet()
{
	delete DestinationMAC;
	delete SourceMAC;
}
