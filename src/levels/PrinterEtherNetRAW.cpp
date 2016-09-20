
#include "PrinterEtherNetRAW.h"

std::string PrinterEtherNetRAW::ID()
{
	return (std::string("EtherNetRAW_Printer"));
}

std::string PrinterEtherNetRAW::Description()
{
	return (std::string("EtherNetRAW frame printer"));
}

PrinterEtherNetRAW::PrinterEtherNetRAW() {
}

Chunk *PrinterEtherNetRAW::Process(Quilt *data, Chunk *p)
{
	ChunkEtherNetRAW *parent = dynamic_cast<ChunkEtherNetRAW *>(p);

	if (parent) {
		const ChunkEtherNet *ethernet = dynamic_cast<const ChunkEtherNet *>(parent->Parent);
		const ChunkEtherNetRAW *raw = dynamic_cast<const ChunkEtherNetRAW *>(parent);
		if (ethernet) {
			std::cout << "EtherNetRAW " << ethernet->SourceMAC->asString()
					<< " -> " << ethernet->DestinationMAC->asString()
					<< " payload_length=" << raw->PayloadLength
					<< "   Data: captured=" << ethernet->Data->CoveredSize << ", size=" << ethernet->Data->Length
					<< "\n";
		}
	}

	return (0);
}
