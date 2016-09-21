
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
