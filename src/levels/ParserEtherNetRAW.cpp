// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "ParserEtherNetRAW.h"

std::string ParserEtherNetRAW::ID()
{
	return (std::string("EthernetRAW"));
}

std::string ParserEtherNetRAW::Description()
{
	return (std::string("Ethernet RAW(IPX) frame"));
}

std::shared_ptr<ChunkEtherNetRAW> ParserEtherNetRAW::Process(const std::shared_ptr<ChunkEtherNet> &ethernet)
{
	if (ethernet->EtherNetType <= 1500) {
		unsigned short b2 = ethernet->Payload->GetShortLEOrFail(0);
		if (0xffff == b2) {
			PayloadQuilt payload = std::make_shared<CPayloadQuilt>(ethernet->Payload, 0);
			std::shared_ptr<ChunkEtherNetRAW> r = std::make_shared<ChunkEtherNetRAW>(ethernet->BaseData, payload, ethernet, ethernet->EtherNetType);
			return (r);
		}
	}

	return (std::shared_ptr<ChunkEtherNetRAW>(nullptr));
}
