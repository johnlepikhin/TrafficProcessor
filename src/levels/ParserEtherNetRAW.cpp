
#include <typeinfo>

#include "ParserEtherNetRAW.h"
#include "PrinterEtherNetRAW.h"

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
		unsigned short b2 = data->GetShortLEOrFail(0);
		if (0xffff == b2) {
			Quilt *containedData = new QuiltCut(data, 0);
			return (new ChunkEtherNetRAW(data, containedData, parent, parent->EtherNetType));
		}
	}

	return (NULL);
}
