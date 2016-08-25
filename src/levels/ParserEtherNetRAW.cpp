
#include <typeinfo>

#include "ParserEtherNetRAW.h"

std::string ParserEtherNetRAW::ID()
{
	return (std::string("EthernetRAW"));
}

std::string ParserEtherNetRAW::Description()
{
	return (std::string("Ethernet RAW(IPX) frame"));
}

ChunkEtherNetRAW *ParserEtherNetRAW::Process(Data *data, Chunk *p)
{
	const unsigned long dataPosition = data->Position;

	ChunkEtherNet *parent = (ChunkEtherNet *)p;

	if (parent->EtherNetType <= 1500) {
		unsigned short b2;
		data->readAhead(&b2, 2, 0);
		if (0xffff == b2) {
			return (new ChunkEtherNetRAW(data, dataPosition, parent, parent->EtherNetType));
		}
	}

	return (NULL);
}
