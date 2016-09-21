
#include "PrinterEtherNet802LLC.h"

std::string PrinterEtherNet802LLC::ID()
{
	return (std::string("EtherNet802LLC_Printer"));
}

std::string PrinterEtherNet802LLC::Description()
{
	return (std::string("EtherNet802LLC frame printer"));
}

PrinterEtherNet802LLC::PrinterEtherNet802LLC() {
}

Chunk *PrinterEtherNet802LLC::Process(Quilt *data, Chunk *p)
{
	ChunkEtherNet802LLC *parent = dynamic_cast<ChunkEtherNet802LLC *>(p);

	if (parent) {
		const ChunkEtherNet *ethernet = dynamic_cast<const ChunkEtherNet *>(parent->Parent);
		const ChunkEtherNet802LLC *chunk = dynamic_cast<const ChunkEtherNet802LLC *>(parent);
		if (ethernet) {
			std::cout << "EtherNet802LLC " << MAC::asString(ethernet->SourceMAC)
					<< " -> " << MAC::asString(ethernet->DestinationMAC)
					<< " payload_length=" << chunk->PayloadLength
					<< " control=" << (int)chunk->Control
					<< " DSAP=" << (int)chunk->DSAP
					<< " SSAP=" << (int)chunk->SSAP
					<< "   Data: captured=" << ethernet->Data->CoveredSize << ", size=" << ethernet->Data->Length
					<< "\n";
		}
	}

	return (0);
}
