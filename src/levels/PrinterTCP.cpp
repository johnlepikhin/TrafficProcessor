
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

Chunk *PrinterTCP::Process(Quilt *data, Chunk *p)
{
	ChunkTCP *parent = dynamic_cast<ChunkTCP *>(p);

	if (parent) {
		try {
			std::cout << "TCP " << parent->SourcePort
					<< " " << parent->DestinationPort
					<< " length=" << parent->PayloadLength
					<< " content=" << (parent->ContainedData->GetSubStringOrFail(0, 20)[0])
					<< "\n";
		} catch (...) {

		}
	}
	return (0);
}
