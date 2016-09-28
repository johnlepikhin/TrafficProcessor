
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

ChunkEtherNet802LLC *ParserEtherNet802LLC::Process(ChunkEtherNet *ethernet)
{
	if (ethernet->EtherNetType <= 1500) {
		unsigned short b2 = ethernet->Payload->GetShortLEOrFail(0);
		if (0xaaaa != b2) {
			unsigned char dsap = b2 >> 8;
			unsigned char ssap = b2 & 0xff;
			unsigned char control = ethernet->Payload->GetCharOrFail(1);
			PayloadQuilt *payload = new PayloadQuilt(ethernet->Payload, 3);
			ChunkEtherNet802LLC *r = new ChunkEtherNet802LLC(
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

	return (NULL);
}
