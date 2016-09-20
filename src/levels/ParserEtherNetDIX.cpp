
#include <typeinfo>

#include "ParserEtherNetDIX.h"
#include "ParserIPv4.h"
#include "ParserIPv6.h"
#include "PrinterEtherNetDIX.h"

std::string ParserEtherNetDIX::ID()
{
	return (std::string("EthernetDIX"));
}

std::string ParserEtherNetDIX::Description()
{
	return (std::string("Ethernet DIX frame"));
}

ChunkEtherNetDIX *ParserEtherNetDIX::Process(Quilt *data, Chunk *p)
{
	ChunkEtherNet *parent = dynamic_cast<ChunkEtherNet *>(p);

	if (parent && parent->EtherNetType > 1500) {
		Quilt *containedData = new QuiltCut(data, 0);
		return (new ChunkEtherNetDIX(data, containedData, parent, parent->EtherNetType));
	}

	return (NULL);
}
