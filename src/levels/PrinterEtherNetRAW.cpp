// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "PrinterEtherNetRAW.h"

std::string PrinterEtherNetRAW::ID()
{
	return (std::string("EtherNetRAW_Printer"));
}

std::string PrinterEtherNetRAW::Description()
{
	return (std::string("EtherNetRAW frame printer"));
}

std::shared_ptr<ChunkRaw> PrinterEtherNetRAW::Process(const std::shared_ptr<ChunkEtherNetRAW> &raw)
{
	std::cout << "EtherNetRAW " << MAC::asString(raw->Parent->SourceMAC)
		<< " -> " << MAC::asString(raw->Parent->DestinationMAC)
		<< " payload_length=" << raw->PayloadLength
		<< "   Data: captured=" << raw->BaseData->CoveredSize << ", size=" << raw->BaseData->Length
		<< "\n";

	return (std::shared_ptr<ChunkRaw>(nullptr));
}
