
#include <typeinfo>

#include "ParserEtherNetSNAP.h"

std::string ParserEtherNetSNAP::ID()
{
	return (std::string("EthernetSNAP"));
}

std::string ParserEtherNetSNAP::Description()
{
	return (std::string("Ethernet SNAP frame"));
}

ChunkEtherNetSNAP *ParserEtherNetSNAP::DoParse(Data *data, Chunk *parent)
{
	const unsigned long dataPosition = data->Position;

	if (typeid(parent) != typeid(ChunkEtherNet)) {
		return (NULL);
	}

	ChunkEtherNet *ethernet = (ChunkEtherNet *)parent;

	if (ethernet->EtherNetType <= 1500) {
		unsigned int b2 = 0;
		data->read(&b2, 3);
		if (0xaaaa03 == b2) {
			unsigned int oui = 0;
			unsigned short pid;
			data->read(&oui, 3);
			oui >>= 8;
			data->read(&pid, 2);
			ChunkEtherNetSNAP *r = new ChunkEtherNetSNAP(
					data,
					dataPosition,
					ethernet,
					ethernet->EtherNetType,
					oui,
					pid);
			return (r);
		}
	}

	return (NULL);
}
