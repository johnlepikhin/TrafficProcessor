
#include "ParserEtherNetRAW.h"

std::string ParserEtherNetRAW::ID()
{
	return (std::string("EthernetRAW"));
}

std::string ParserEtherNetRAW::Description()
{
	return (std::string("Ethernet RAW(IPX) frame"));
}

std::shared_ptr<ChunkEtherNetRAW> ParserEtherNetRAW::Process(std::shared_ptr<ChunkEtherNet> ethernet)
{
	if (ethernet->EtherNetType <= 1500) {
		unsigned short b2 = ethernet->Payload->GetShortLEOrFail(0);
		if (0xffff == b2) {
			PayloadQuilt payload(new CPayloadQuilt(ethernet->Payload, 0));
			std::shared_ptr<ChunkEtherNetRAW> r(new ChunkEtherNetRAW(ethernet->BaseData, payload, ethernet, ethernet->EtherNetType));
			return (r);
		}
	}

	return (std::shared_ptr<ChunkEtherNetRAW>(nullptr));
}
