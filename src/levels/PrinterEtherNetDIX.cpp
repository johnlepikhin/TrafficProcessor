
#include "PrinterEtherNetDIX.h"

std::string PrinterEtherNetDIX::ID()
{
	return (std::string("EtherNetDIX_Printer"));
}

std::string PrinterEtherNetDIX::Description()
{
	return (std::string("EtherNetDIX frame printer"));
}

PrinterEtherNetDIX::PrinterEtherNetDIX() {
}

Chunk *PrinterEtherNetDIX::Process(const Quilt *data, const Chunk *p)
{
	const ChunkEtherNetDIX *parent = dynamic_cast<const ChunkEtherNetDIX *>(p);

	if (parent) {
		const ChunkEtherNet *ethernet = dynamic_cast<const ChunkEtherNet *>(parent->Parent);
		const ChunkEtherNetDIX *dix = dynamic_cast<const ChunkEtherNetDIX *>(parent);
		if (ethernet) {
			std::cout << "EtherNetDIX " << ethernet->SourceMAC->asString()
					<< " -> " << ethernet->DestinationMAC->asString()
					<< " type=" << dix->EtherNetType
					<< "   Data: captured=" << ethernet->Data->CoveredSize << ", size=" << ethernet->Data->Length
					<< "\n";
		}
	}

	return (0);
}
