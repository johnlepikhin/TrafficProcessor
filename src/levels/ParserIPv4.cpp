
#include <typeinfo>

#include "ParserIPv4.h"
#include "PrinterIPv4.h"

std::string ParserIPv4::ID()
{
	return (std::string("IPv4"));
}

std::string ParserIPv4::Description()
{
	return (std::string("IPv4 packet"));
}

ChunkIPv4 *ParserIPv4::Process(const Quilt *data, const Chunk *p)
{
	const ChunkEtherNetDIX *parentDIX = dynamic_cast<const ChunkEtherNetDIX *>(p);
	if (parentDIX) {
		ChunkEtherNet *parentEthernet = (ChunkEtherNet *)(parentDIX->Parent);

		if (parentEthernet && parentEthernet->EtherNetType == 0x800) {
			unsigned char IHL32bit = data->GetCharOrFail(0);
			IHL32bit = IHL32bit & 0xf;

			IPv4Addr *SrcIP = new IPv4Addr(*data, 12);
			IPv4Addr *DstIP = new IPv4Addr(*data, 16);

			unsigned short PktLength = data->GetShortLEOrFail(2);
			PktLength = (short)((PktLength>>8) | (PktLength<<8));

			unsigned char flags = data->GetCharOrFail(6);
			bool FlagDontFragment = flags & 0x40;
			bool FlagIsFragmented = flags & 0x20;

			unsigned short FragmentOffset = data->GetShortLEOrFail(6);
			FragmentOffset = ((FragmentOffset >> 8) + ((FragmentOffset & 0x1f) << 8)) << 3;

			unsigned short ID = data->GetShortLEOrFail(4);

			unsigned char TTL = data->GetCharOrFail(8);

			unsigned char Protocol = data->GetCharOrFail(9);

			Protocol = data->GetCharOrFail(9);

			const QuiltCut *payload = new QuiltCut(data, IHL32bit*4);

			ChunkIPv4 *r = new ChunkIPv4(
					data,
					payload,
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
