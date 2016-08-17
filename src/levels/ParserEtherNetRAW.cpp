
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

ChunkEtherNetRAW *ParserEtherNetRAW::DoParse(Data *data, Chunk *parent)
{
	const unsigned long dataPosition = data->Position;

	if (typeid(parent) != typeid(ChunkEtherNet)) {
		return (NULL);
	}

	ChunkEtherNet *ethernet = (ChunkEtherNet *)parent;

	if (ethernet->EtherNetType <= 1500) {
		unsigned short b2;
		data->readAhead(&b2, 2, 0);
		if (0xffff == b2) {
			return (new ChunkEtherNetRAW(data, dataPosition, ethernet, ethernet->EtherNetType));
		}
	}

	return (NULL);
}
