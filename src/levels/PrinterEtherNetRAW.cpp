
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

ChunkRaw *PrinterEtherNetRAW::Process(ChunkEtherNetRAW *raw)
{
	std::cout << "EtherNetRAW " << MAC::asString(raw->Parent->SourceMAC)
		<< " -> " << MAC::asString(raw->Parent->DestinationMAC)
		<< " payload_length=" << raw->PayloadLength
		<< "   Data: captured=" << raw->BaseData->CoveredSize << ", size=" << raw->BaseData->Length
		<< "\n";

	return (0);
}
