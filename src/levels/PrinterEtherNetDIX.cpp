
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

Chunk *PrinterEtherNetDIX::Process(Data *data, Chunk *p)
{
	ChunkEtherNetDIX *parent = dynamic_cast<ChunkEtherNetDIX *>(p);

	if (parent) {
		const ChunkEtherNet *ethernet = dynamic_cast<const ChunkEtherNet *>(parent->Parent);
		if (ethernet) {
			std::cout << "EtherNetDIX " << ethernet->SourceMAC->asString()
					<< " -> " << ethernet->DestinationMAC->asString()
					<< " type=" << ethernet->EtherNetType
					<< "   Data: captured=" << ethernet->DataPtr->Captured << ", size=" << ethernet->DataPtr->Size
					<< "\n";
		}
	}

	return (0);
}
