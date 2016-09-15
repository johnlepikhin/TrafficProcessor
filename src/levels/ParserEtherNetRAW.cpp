
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

ChunkEtherNetRAW *ParserEtherNetRAW::Process(const Quilt *data, const Chunk *p)
{
	const ChunkEtherNet *parent = dynamic_cast<const ChunkEtherNet *>(p);

	if (parent && parent->EtherNetType <= 1500) {
		unsigned short b2 = data->GetShortBEOrFail(0);
		if (0xffff == b2) {
			return (new ChunkEtherNetRAW(data, data, parent, parent->EtherNetType));
		}
	}

	return (NULL);
}
