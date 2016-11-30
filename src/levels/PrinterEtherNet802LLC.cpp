// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

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

std::shared_ptr<ChunkRaw> PrinterEtherNet802LLC::Process(std::shared_ptr<ChunkEtherNet802LLC> llc)
{
	std::cout << "EtherNet802LLC " << MAC::asString(llc->Parent->SourceMAC)
		<< " -> " << MAC::asString(llc->Parent->DestinationMAC)
		<< " payload_length=" << llc->PayloadLength
		<< " control=" << (int)llc->Control
		<< " DSAP=" << (int)llc->DSAP
		<< " SSAP=" << (int)llc->SSAP
		<< "   Data: captured=" << llc->BaseData->CoveredSize << ", size=" << llc->BaseData->Length
		<< "\n";

	return (std::shared_ptr<ChunkRaw>(nullptr));
}
