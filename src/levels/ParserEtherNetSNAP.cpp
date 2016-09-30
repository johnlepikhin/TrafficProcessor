
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

std::shared_ptr<ChunkEtherNetSNAP> ParserEtherNetSNAP::Process(std::shared_ptr<ChunkEtherNet> ethernet)
{
	if (ethernet->EtherNetType <= 1500) {
		unsigned int b3 = ethernet->Payload->GetShortLEOrFail(3);
		if (0xaaaa03 == b3) {
			unsigned int oui = 0;
			ethernet->Payload->CopyBytesOrFail((char *)&oui+1, 2, 3);
			unsigned short pid = ethernet->Payload->GetShortLEOrFail(5);

			PayloadQuilt payload(new CPayloadQuilt(ethernet->Payload, 8));

			std::shared_ptr<ChunkEtherNetSNAP> r(new ChunkEtherNetSNAP(
					ethernet->BaseData,
					payload,
					ethernet,
					ethernet->EtherNetType,
					oui,
					pid));
			return (r);
		}
	}

	return (std::shared_ptr<ChunkEtherNetSNAP>(nullptr));
}
