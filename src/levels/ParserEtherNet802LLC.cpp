
#include <typeinfo>

#include "ParserEtherNet802LLC.h"
#include "PrinterEtherNet802LLC.h"

std::string ParserEtherNet802LLC::ID()
{
	return (std::string("Ethernet802LLC"));
}

std::string ParserEtherNet802LLC::Description()
{
	return (std::string("Ethernet 802.3 LLC frame"));
}

std::shared_ptr<ChunkEtherNet802LLC> ParserEtherNet802LLC::Process(std::shared_ptr<ChunkEtherNet> ethernet)
{
	if (ethernet->EtherNetType <= 1500) {
		unsigned short b2 = ethernet->Payload->GetShortLEOrFail(0);
		if (0xaaaa != b2) {
			unsigned char dsap = b2 >> 8;
			unsigned char ssap = b2 & 0xff;
			unsigned char control = ethernet->Payload->GetCharOrFail(1);
			PayloadQuilt payload = std::make_shared<CPayloadQuilt>(ethernet->Payload, 3);
			std::shared_ptr<ChunkEtherNet802LLC> r = std::make_shared<ChunkEtherNet802LLC>(
					ethernet->BaseData,
					payload,
					ethernet,
					ethernet->EtherNetType,
					dsap,
					ssap,
					control);

			return (r);
		}
	}

	return (std::shared_ptr<ChunkEtherNet802LLC>(nullptr));
}
