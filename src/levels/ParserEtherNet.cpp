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
	uint64_t DA = MAC::Make(buf, 0);
	uint64_t SA = MAC::Make(buf, 6);

	uint16_t eType;
	buf.copy(reinterpret_cast<char *>(&eType), 2, 12);
	eType = (eType << 8) | (eType >> 8);

	PayloadQuilt payload = std::make_shared<CPayloadQuilt>(data, 14);

	std::shared_ptr<ChunkEtherNet> r = std::make_shared<ChunkEtherNet>(data, payload, DA, SA, eType);

	return (r);
}
