
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
			unsigned char IHL32bit =  data->read1Ahead(0);
			IHL32bit = IHL32bit & 0xf;

			IPv4Addr *SrcIP = new IPv4Addr(data, 12);
			IPv4Addr *DstIP = new IPv4Addr(data, 16);

			unsigned short PktLength = data->read2Ahead(2);
			PktLength = (short)((PktLength>>8) | (PktLength<<8));

			unsigned char flags = data->read1Ahead(6);
			bool FlagDontFragment = flags & 0x40;
			bool FlagIsFragmented = flags & 0x20;

			unsigned short FragmentOffset = data->read2Ahead(6);
			FragmentOffset = ((FragmentOffset >> 8) + ((FragmentOffset & 0x1f) << 8)) << 3;

			unsigned short ID = data->read2Ahead(4);

			unsigned char TTL = data->read1Ahead(8);

			unsigned char Protocol = data->read1Ahead(9);

			Protocol = (unsigned char)data->getPtrAtOffset(9)[0];

			data->ignore(IHL32bit*4);

			ChunkIPv4 *r = new ChunkIPv4(
					data,
					dataPosition,
					parentDIX,
					IHL32bit,
					SrcIP,
					DstIP,
					PktLength,
					Protocol,
					FlagDontFragment,
					FlagIsFragmented,
					ID,
					FragmentOffset,
					TTL);
			return (r);
		}
	}

	return (NULL);
}
