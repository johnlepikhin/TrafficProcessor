
#include "PrinterEtherNetSNAP.h"

std::string PrinterEtherNetSNAP::ID()
{
	return (std::string("EtherNetSNAP_Printer"));
}

std::string PrinterEtherNetSNAP::Description()
{
	return (std::string("EtherNetSNAP frame printer"));
}

PrinterEtherNetSNAP::PrinterEtherNetSNAP() {
}

Chunk *PrinterEtherNetSNAP::Process(const Quilt *data, const Chunk *p)
{
	const ChunkEtherNetSNAP *parent = dynamic_cast<const ChunkEtherNetSNAP *>(p);

	if (parent) {
		const ChunkEtherNet *ethernet = dynamic_cast<const ChunkEtherNet *>(parent->Parent);
		const ChunkEtherNetSNAP *snap = dynamic_cast<const ChunkEtherNetSNAP *>(parent);
		if (ethernet) {
			std::cout << "EtherNetSNAP " << ethernet->SourceMAC->asString()
					<< " -> " << ethernet->DestinationMAC->asString()
					<< " payload_length=" << snap->PayloadLength
					<< " OUI=" << snap->OUI
					<< " PID=" << snap->PID
					<< "   Data: captured=" << ethernet->Data->CoveredSize << ", size=" << ethernet->Data->Length
					<< "\n";
		}
	}

	return (0);
}
