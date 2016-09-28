
#include "ChunkEtherNet.h"

ChunkEtherNet::ChunkEtherNet(BaseQuilt *baseData
		, PayloadQuilt *payload
		, const unsigned long long destinationMAC
		, const unsigned long long sourceMAC
		, const unsigned short ethernetType)
	: Chunk<BaseQuilt>(baseData, payload)
	, DestinationMAC(destinationMAC)
	, SourceMAC(sourceMAC)
	, EtherNetType(ethernetType)
{
}
