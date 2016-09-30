
#include "PrinterEtherNetDIX.h"

std::string PrinterEtherNetDIX::ID()
{
	return (std::string("EtherNetDIX_Printer"));
}

std::string PrinterEtherNetDIX::Description()
{
	return (std::string("EtherNetDIX frame printer"));
}

std::shared_ptr<ChunkRaw> PrinterEtherNetDIX::Process(std::shared_ptr<ChunkEtherNetDIX> dix)
{
	const std::shared_ptr<ChunkEtherNet> ethernet = dix->Parent;
	std::cout << "EtherNetDIX " << MAC::asString(ethernet->SourceMAC)
		<< " -> " << MAC::asString(ethernet->DestinationMAC)
		<< " type=" << dix->EtherNetType
		<< "   Data: captured=" << dix->BaseData->CoveredSize << ", size=" << dix->BaseData->Length
		<< "\n";

	return (std::shared_ptr<ChunkRaw>(nullptr));
}
