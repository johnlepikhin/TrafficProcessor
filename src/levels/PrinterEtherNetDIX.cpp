
#include "PrinterEtherNetDIX.h"

std::string PrinterEtherNetDIX::ID()
{
	return (std::string("EtherNetDIX_Printer"));
}

std::string PrinterEtherNetDIX::Description()
{
	return (std::string("EtherNetDIX frame printer"));
}

ChunkRaw *PrinterEtherNetDIX::Process(ChunkEtherNetDIX *dix)
{
	const ChunkEtherNet *ethernet = dix->Parent;
	std::cout << "EtherNetDIX " << MAC::asString(ethernet->SourceMAC)
		<< " -> " << MAC::asString(ethernet->DestinationMAC)
		<< " type=" << dix->EtherNetType
		<< "   Data: captured=" << dix->BaseData->CoveredSize << ", size=" << dix->BaseData->Length
		<< "\n";

	return (NULL);
}
