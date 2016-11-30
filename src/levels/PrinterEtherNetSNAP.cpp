// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "PrinterEtherNetSNAP.h"

std::string PrinterEtherNetSNAP::ID()
{
	return (std::string("EtherNetSNAP_Printer"));
}

std::string PrinterEtherNetSNAP::Description()
{
	return (std::string("EtherNetSNAP frame printer"));
}

std::shared_ptr<ChunkRaw> PrinterEtherNetSNAP::Process(const std::shared_ptr<ChunkEtherNetSNAP> &snap)
{
	std::cout << "EtherNetSNAP " << MAC::asString(snap->Parent->SourceMAC)
		<< " -> " << MAC::asString(snap->Parent->DestinationMAC)
		<< " payload_length=" << snap->PayloadLength
		<< " OUI=" << snap->OUI
		<< " PID=" << snap->PID
		<< "   Data: captured=" << snap->BaseData->CoveredSize << ", size=" << snap->BaseData->Length
		<< "\n";

	return (std::shared_ptr<ChunkRaw>(nullptr));
}
