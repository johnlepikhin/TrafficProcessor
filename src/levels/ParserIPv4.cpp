
#include <typeinfo>

#include "ParserIPv4.h"
#include "PrinterIPv4.h"

ParserIPv4::ParserIPv4()
{
	std::vector<Processor *> followers;
	followers.push_back(new PrinterIPv4());
	SetFollowers(&followers);
}


std::string ParserIPv4::ID()
{
	return (std::string("IPv4"));
}

std::string ParserIPv4::Description()
{
	return (std::string("IPv4 packet"));
}

ChunkIPv4 *ParserIPv4::DoParse(Data *data, ChunkEtherNetDIX *parent)
{
	const unsigned long dataPosition = data->Position;

	if (parent->EtherNetType == 0x800) {
		char b;
		data->readAhead(&b, 1, 0);
		unsigned char IHL32bit = b & 0xf;
		IPv4Addr *SrcIP = new IPv4Addr(data, 12);
		IPv4Addr *DstIP = new IPv4Addr(data, 16);
		unsigned short PktLength;
		unsigned char Protocol;
		data->readAhead(&PktLength, 2, 2);
		PktLength = (PktLength>>8) | (PktLength<<8);
		data->readAhead(&Protocol, 1, 9);
		Protocol = (unsigned char)data->getPtrAtOffset(9)[0];
		data->ignore(IHL32bit*4);
		return (new ChunkIPv4(data, dataPosition, parent, IHL32bit, SrcIP, DstIP, PktLength, Protocol));
	}

	return (NULL);
}
