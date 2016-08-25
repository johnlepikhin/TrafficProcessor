
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

ChunkEtherNet802LLC *ParserEtherNet802LLC::Process(Data *data, Chunk *p)
{
	const unsigned long dataPosition = data->Position;

	ChunkEtherNet *parent = (ChunkEtherNet *)p;

	if (parent->EtherNetType <= 1500) {
		unsigned short b2 = 0;
		data->read(&b2, 2);
		if (0xaaaa != b2) {
			unsigned char dsap = b2 >> 8;
			unsigned char ssap = b2 & 0xff;
			unsigned char control;
			data->read(&control, 1);
			ChunkEtherNet802LLC *r = new ChunkEtherNet802LLC(
					data,
					dataPosition,
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
