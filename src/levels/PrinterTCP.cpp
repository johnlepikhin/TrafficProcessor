
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
		std::cout << "TCP srcp=" << chunk->SourcePort
				<< " dstp=" << chunk->DestinationPort
				<< " seq=" << chunk->SeqNumber
				<< " ack=" << chunk->ConfirmNumber
				<< " flgACK=" << chunk->FlagACK
				<< " flgSYN=" << chunk->FlagSYN
				<< " flgFIN=" << chunk->FlagFIN
				<< " length=" << chunk->PayloadLength
				<< " content=" << payload[0]
				<< "\n";

		delete payload;
	} catch (...) {
		std::cout << "TCP srcp=" << chunk->SourcePort
				<< " dstp=" << chunk->DestinationPort
				<< " seq=" << chunk->SeqNumber
				<< " ack=" << chunk->ConfirmNumber
				<< " flgACK=" << chunk->FlagACK
				<< " flgSYN=" << chunk->FlagSYN
				<< " flgFIN=" << chunk->FlagFIN
				<< "\n";
	}

	return (std::shared_ptr<ChunkRaw>(nullptr));
}
