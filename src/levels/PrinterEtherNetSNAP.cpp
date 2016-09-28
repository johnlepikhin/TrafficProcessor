
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

ChunkRaw *PrinterEtherNetSNAP::Process(ChunkEtherNetSNAP *snap)
{
	std::cout << "EtherNetSNAP " << MAC::asString(snap->Parent->SourceMAC)
		<< " -> " << MAC::asString(snap->Parent->DestinationMAC)
		<< " payload_length=" << snap->PayloadLength
		<< " OUI=" << snap->OUI
		<< " PID=" << snap->PID
		<< "   Data: captured=" << snap->BaseData->CoveredSize << ", size=" << snap->BaseData->Length
		<< "\n";

	return (0);
}
