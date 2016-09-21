
#include "ChunkEtherNet.h"

ChunkEtherNet::ChunkEtherNet(Quilt *data,
		Quilt *containedData,
		const unsigned long long destinationMAC,
		const unsigned long long sourceMAC,
		const unsigned short ethernetType)
	: Chunk(data, containedData)
	, DestinationMAC(destinationMAC)
	, SourceMAC(sourceMAC)
	, EtherNetType(ethernetType)
{
}
