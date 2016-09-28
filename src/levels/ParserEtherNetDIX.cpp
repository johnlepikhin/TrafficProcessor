
#include <typeinfo>

#include "ParserEtherNetDIX.h"
//#include "ParserIPv4.h"
//#include "ParserIPv6.h"

std::string ParserEtherNetDIX::ID()
{
	return (std::string("EthernetDIX"));
}

std::string ParserEtherNetDIX::Description()
{
	return (std::string("Ethernet DIX frame"));
}

ChunkEtherNetDIX *ParserEtherNetDIX::Process(ChunkEtherNet *parent)
{
	if (parent->EtherNetType > 1500) {
		PayloadQuilt *payload = new PayloadQuilt(parent->Payload, 0);
		return (new ChunkEtherNetDIX(parent->BaseData, payload, parent, parent->EtherNetType));
	}

	return (NULL);
}
