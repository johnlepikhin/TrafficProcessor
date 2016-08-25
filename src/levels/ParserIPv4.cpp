
#include <typeinfo>

#include "ParserIPv4.h"
#include "PrinterIPv4.h"

ParserIPv4::ParserIPv4()
{
	AddFollower(new PrinterIPv4());
}



std::string ParserIPv4::ID()
{
	return (std::string("IPv4"));
}

std::string ParserIPv4::Description()
{
	return (std::string("IPv4 packet"));
}

ChunkIPv4 *ParserIPv4::Process(Data *d, Chunk *p)
{
	Data *data = d;
	const unsigned long dataPosition = data->Position;

	ChunkEtherNetDIX *parentDIX = dynamic_cast<ChunkEtherNetDIX *>(p);
	if (parentDIX) {
		ChunkEtherNet *parentEthernet = (ChunkEtherNet *)(parentDIX->Parent);

		if (parentEthernet && parentEthernet->EtherNetType == 0x800) {
			char b;
			data->readAhead(&b, 1, 0);
			unsigned char IHL32bit = b & 0xf;
			IPv4Addr *SrcIP = new IPv4Addr(data, 12);
			IPv4Addr *DstIP = new IPv4Addr(data, 16);
			unsigned short PktLength;
			unsigned char Protocol;
			data->readAhead(&PktLength, 2, 2);
			PktLength = (short)((PktLength>>8) | (PktLength<<8));
			data->readAhead(&Protocol, 1, 9);
			Protocol = (unsigned char)data->getPtrAtOffset(9)[0];
			data->ignore(IHL32bit*4);

			return (new ChunkIPv4(data, dataPosition, parentDIX, IHL32bit, SrcIP, DstIP, PktLength, Protocol));
		}
	}

	return (NULL);
}
