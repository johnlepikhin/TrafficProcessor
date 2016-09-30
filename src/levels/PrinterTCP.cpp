
#include "PrinterTCP.h"
#include <iostream>

std::string PrinterTCP::ID()
{
	return (std::string("TCP_Printer"));
}

std::string PrinterTCP::Description()
{
	return (std::string("TCP printer"));
}

std::shared_ptr<ChunkRaw> PrinterTCP::Process(std::shared_ptr<ChunkTCP> chunk)
{
	try {
		std::string *payload = chunk->Payload->GetSubStringOrFail(0, 20);
		std::cout << "TCP " << chunk->SourcePort
				<< " " << chunk->DestinationPort
				<< " length=" << chunk->PayloadLength
				<< " content=" << payload[0]
				<< "\n";

		delete payload;
	} catch (...) {

	}

	return (std::shared_ptr<ChunkRaw>(nullptr));
}
