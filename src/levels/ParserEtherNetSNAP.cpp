// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include <typeinfo>

#include "ParserEtherNetSNAP.h"
#include "PrinterEtherNetSNAP.h"

std::string ParserEtherNetSNAP::ID()
{
	return (std::string("EthernetSNAP"));
}

std::string ParserEtherNetSNAP::Description()
{
	return (std::string("Ethernet SNAP frame"));
}

std::shared_ptr<ChunkEtherNetSNAP> ParserEtherNetSNAP::Process(const std::shared_ptr<ChunkEtherNet> &ethernet)
{
	if (ethernet->EtherNetType <= 1500) {
		unsigned int b3 = ethernet->Payload->GetShortLEOrFail(3);
		if (0xaaaa03 == b3) {
			uint8_t dsap = b3 >> 16;
			uint8_t ssap = (b3 >> 8) & 0xff;
			uint8_t control = b3 & 0xff;

			uint32_t oui = 0;
			ethernet->Payload->CopyBytesOrFail(reinterpret_cast<char *>(&oui+1), 2, 3); //-V206
			uint16_t pid = ethernet->Payload->GetShortLEOrFail(5);

			PayloadQuilt payload = std::make_shared<CPayloadQuilt>(ethernet->Payload, 8);

			std::shared_ptr<ChunkEtherNetSNAP> r = std::make_shared<ChunkEtherNetSNAP>(
					ethernet->BaseData,
					payload,
					ethernet,
					ethernet->EtherNetType,  // actually this is length
					dsap,
					ssap,
					control,
					oui,
					pid);
			return (r);
		}
	}

	return (std::shared_ptr<ChunkEtherNetSNAP>(nullptr));
}
