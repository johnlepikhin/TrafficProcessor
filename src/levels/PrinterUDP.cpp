
#include "PrinterUDP.h"
#include <iostream>

std::string PrinterUDP::ID()
{
	return (std::string("UDP_Printer"));
}

std::string PrinterUDP::Description()
{
	return (std::string("UDP printer"));
}

std::shared_ptr<ChunkRaw> PrinterUDP::Process(std::shared_ptr<ChunkUDP> chunk)
{
	try {
		std::string *payload = chunk->Payload->GetSubStringOrFail(0, 20);
		std::cout << "UDP srcp=" << chunk->SourcePort
				<< " dstp=" << chunk->DestinationPort
				<< " length=" << chunk->PayloadLength
				<< " content=" << payload[0]
				<< "\n";

		delete payload;
	} catch (...) {
		std::cout << "TCP srcp=" << chunk->SourcePort
				<< " dstp=" << chunk->DestinationPort
				<< "\n";
	}

	return (std::shared_ptr<ChunkRaw>(nullptr));
}
