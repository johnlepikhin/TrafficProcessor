/*
 * PrinterIPv4.cpp
 *
 *  Created on: 19 авг. 2016 г.
 *      Author: eugene
 */

#include "PrinterIPv4.h"

std::string PrinterIPv4::ID()
{
	return (std::string("IPv4_Printer"));
}

std::string PrinterIPv4::Description()
{
	return (std::string("IPv4 packet printer"));
}

ChunkIPv4 *PrinterIPv4::Process(Data *data, ChunkIPv4 *parent)
{
	std::cout << "IPv4 " << parent->SrcIP->asString() << " " << parent->DstIP->asString() << "\n";
	return (0);
}
