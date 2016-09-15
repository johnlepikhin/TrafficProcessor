
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

ChunkEtherNet802LLC *ParserEtherNet802LLC::Process(const Quilt *data, const Chunk *p)
{
	const ChunkEtherNet *parent = dynamic_cast<const ChunkEtherNet *>(p);

	if (parent && parent->EtherNetType <= 1500) {
		unsigned short b2 = data->GetShortBEOrFail(0);
		if (0xaaaa != b2) {
			unsigned char dsap = b2 >> 8;
			unsigned char ssap = b2 & 0xff;
			unsigned char control = data->GetCharOrFail(1);
			const Quilt *containedData = new QuiltCut(*data, 3);
			ChunkEtherNet802LLC *r = new ChunkEtherNet802LLC(
					data,
					containedData,
					parent,
					parent->EtherNetType,
					dsap,
					ssap,
					control);
			return (r);
		}
	}

	return (NULL);
}
