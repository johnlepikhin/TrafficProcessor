
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

std::shared_ptr<ChunkEtherNetDIX> ParserEtherNetDIX::Process(std::shared_ptr<ChunkEtherNet> parent)
{
	if (parent->EtherNetType > 1500) {
		PayloadQuilt payload(new CPayloadQuilt(parent->Payload, 0));
		std::shared_ptr<ChunkEtherNetDIX> r(new ChunkEtherNetDIX(parent->BaseData, payload, parent, parent->EtherNetType));
		return (r);
	}

	return (std::shared_ptr<ChunkEtherNetDIX>(nullptr));
}
