
#include <typeinfo>

#include "ParserEtherNetSNAP.h"
#include "PrinterEtherNetSNAP.h"

std::string ParserEtherNetSNAP::ID()
{
	return (std::string("EthernetSNAP"));
}

std::string ParserEtherNetSNAP::Description()
{
	return (std::string("Ethernet SNAP frame"));
}

ChunkEtherNetSNAP *ParserEtherNetSNAP::Process(const Quilt *data, const Chunk *p)
{
	const ChunkEtherNet *parent = dynamic_cast<const ChunkEtherNet *>(p);

	if (parent && parent->EtherNetType <= 1500) {
		unsigned int b3 = data->GetShortLEOrFail(3);
		if (0xaaaa03 == b3) {
			unsigned int oui = 0;
			data->CopyBytesOrFail((char *)&oui+1, 2, 3);
			unsigned short pid = data->GetShortLEOrFail(5);

			const Quilt *containedData = new QuiltCut(data, 8);

			ChunkEtherNetSNAP *r = new ChunkEtherNetSNAP(
					data,
					containedData,
					parent,
					parent->EtherNetType,
					oui,
					pid);
			return (r);
		}
	}

	return (NULL);
}
