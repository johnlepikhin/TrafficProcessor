
#include "ParserEtherNet.h"
//#include "ParserEtherNetDIX.h"
//#include "ParserEtherNet802LLC.h"
//#include "ParserEtherNetRAW.h"
//#include "ParserEtherNetSNAP.h"

std::string ParserEtherNet::ID()
{
	return (std::string("Ethernet"));
}

std::string ParserEtherNet::Description()
{
	return (std::string("Ethernet frame"));
}

ChunkEtherNet *ParserEtherNet::Process(BaseQuilt *data)
{
	unsigned long long DA = MAC::Make(*data, 0);
	unsigned long long SA = MAC::Make(*data, 6);

	unsigned short eType = data->GetShortBEOrFail(12);
	PayloadQuilt *payload = new PayloadQuilt(data, 14);
	ChunkEtherNet *r = new ChunkEtherNet(data, payload, DA, SA, eType); // TODO

	return (r);
}
