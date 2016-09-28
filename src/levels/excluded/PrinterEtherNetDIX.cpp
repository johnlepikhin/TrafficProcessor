
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

Chunk *PrinterEtherNetDIX::Process(Quilt *data, Chunk *p)
{
	ChunkEtherNetDIX *parent = dynamic_cast<ChunkEtherNetDIX *>(p);

	if (parent) {
		const ChunkEtherNet *ethernet = dynamic_cast<const ChunkEtherNet *>(parent->Parent);
		const ChunkEtherNetDIX *dix = dynamic_cast<const ChunkEtherNetDIX *>(parent);
		if (ethernet) {
			std::cout << "EtherNetDIX " << MAC::asString(ethernet->SourceMAC)
					<< " -> " << MAC::asString(ethernet->DestinationMAC)
					<< " type=" << dix->EtherNetType
					<< "   Data: captured=" << ethernet->Data->CoveredSize << ", size=" << ethernet->Data->Length
					<< "\n";
		}
	}

	return (0);
}
