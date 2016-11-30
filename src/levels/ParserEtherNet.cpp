// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "ParserEtherNet.h"

std::string ParserEtherNet::ID()
{
	return (std::string("Ethernet"));
}

std::string ParserEtherNet::Description()
{
	return (std::string("Ethernet frame"));
}

std::shared_ptr<ChunkEtherNet> ParserEtherNet::Process(const BaseQuilt &data)
{
	std::string buf;
	buf.resize(14);
	data->CopyBytesOrFail(&(buf.at(0)), 0, 14);
	unsigned long long DA = MAC::Make(buf, 0);
	unsigned long long SA = MAC::Make(buf, 6);

	unsigned short eType;
	buf.copy((char *)&eType, 2, 12);
	eType = (eType << 8) | (eType >> 8);

	PayloadQuilt payload = std::make_shared<CPayloadQuilt>(data, 14);

	std::shared_ptr<ChunkEtherNet> r = std::make_shared<ChunkEtherNet>(data, payload, DA, SA, eType);

	return (r);
}
