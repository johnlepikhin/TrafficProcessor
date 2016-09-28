
#include "ParserEtherNetRAW.h"

std::string ParserEtherNetRAW::ID()
{
	return (std::string("EthernetRAW"));
}

std::string ParserEtherNetRAW::Description()
{
	return (std::string("Ethernet RAW(IPX) frame"));
}

ChunkEtherNetRAW *ParserEtherNetRAW::Process(ChunkEtherNet *ethernet)
{
	if (ethernet->EtherNetType <= 1500) {
		unsigned short b2 = ethernet->Payload->GetShortLEOrFail(0);
		if (0xffff == b2) {
			PayloadQuilt *payload = new PayloadQuilt(ethernet->Payload, 0);
			return (new ChunkEtherNetRAW(ethernet->BaseData, payload, ethernet, ethernet->EtherNetType));
		}
	}

	return (NULL);
}
