// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

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

std::shared_ptr<ChunkEtherNetDIX> ParserEtherNetDIX::Process(const std::shared_ptr<ChunkEtherNet> &parent)
{
	if (parent->EtherNetType > 1500) {
		std::shared_ptr<ChunkEtherNetDIX> r = std::make_shared<ChunkEtherNetDIX>(parent->BaseData, parent->Payload, parent, parent->EtherNetType);
		return (r);
	}

	return (std::shared_ptr<ChunkEtherNetDIX>(nullptr));
}
