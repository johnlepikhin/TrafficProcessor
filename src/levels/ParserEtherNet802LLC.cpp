// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include <typeinfo>

#include "ParserEtherNet802LLC.h"

std::string ParserEtherNet802LLC::ID()
{
	return (std::string("Ethernet802LLC"));
}

std::string ParserEtherNet802LLC::Description()
{
	return (std::string("Ethernet 802.3 LLC frame"));
}

std::shared_ptr<ChunkEtherNet802LLC> ParserEtherNet802LLC::Process(const std::shared_ptr<ChunkEtherNet> &ethernet)
{
	if (ethernet->EtherNetType <= 1500) {
		unsigned short b2 = ethernet->Payload->GetShortLEOrFail(0);
		if (0xaaaa != b2 && 0xffff != b2) {
			unsigned char dsap = b2 >> 8;
			unsigned char ssap = b2 & 0xff;
			unsigned char control = ethernet->Payload->GetCharOrFail(2);
			PayloadQuilt payload = std::make_shared<CPayloadQuilt>(ethernet->Payload, 2); // TODO offset should be 3, but there's no control byte in real data!
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
