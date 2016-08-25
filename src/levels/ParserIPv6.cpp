
#include <typeinfo>

#include "ParserIPv6.h"

std::string ParserIPv6::ID()
{
	return (std::string("IPv6"));
}

std::string ParserIPv6::Description()
{
	return (std::string("IPv6 packet"));
}

ChunkIPv6 *ParserIPv6::Process(Data *data, Chunk *p)
{
	const unsigned long dataPosition = data->Position;

	ChunkEtherNetDIX *parentDIX = (ChunkEtherNetDIX *)p;
	ChunkEtherNet *parentEthernet = (ChunkEtherNet *)parentDIX->Parent;

	if (parentEthernet->EtherNetType == 0x86dd) {
		IPv6Addr *srcIP = new IPv6Addr(data, 8);
		IPv6Addr *dstIP = new IPv6Addr(data, 24);

		unsigned char nextHdr = data->getPtrAtOffset(2)[0];
		data->ignore(40);
		while (0 == nextHdr
				|| 43 == nextHdr
				|| 44 == nextHdr
				|| 50 == nextHdr
				|| 51 == nextHdr
				|| 60 == nextHdr) {
			nextHdr = data->getPtrAtOffset(0)[0];
			data->ignore(4);
		}

		return (new ChunkIPv6(data, dataPosition, parentDIX, srcIP, dstIP));
	}

	return (NULL);
}
