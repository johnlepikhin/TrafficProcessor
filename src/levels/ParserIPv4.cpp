
#include <typeinfo>

#include "ParserIPv4.h"

std::string ParserIPv4::ID()
{
	return (std::string("IPv4_Fragment"));
}

std::string ParserIPv4::Description()
{
	return (std::string("IPv4 packet fragment"));
}

std::shared_ptr<ChunkIPv4> ParserIPv4::Process(std::shared_ptr<ChunkEtherNetDIX> dix)
{
	if (dix->Parent->EtherNetType == 0x800) {
		unsigned char IHL32bit = dix->Payload->GetCharOrFail(0);
		IHL32bit = IHL32bit & 0xf;

		unsigned long SrcIP = IPv4Addr::Make(*dix->Payload, 12);
		unsigned long DstIP = IPv4Addr::Make(*dix->Payload, 16);

		unsigned short PktLength = dix->Payload->GetShortLEOrFail(2);
		PktLength = (short)((PktLength>>8) | (PktLength<<8));

		unsigned short PayloadLength = PktLength - IHL32bit*4;

		unsigned char flags = dix->Payload->GetCharOrFail(6);
		bool FlagDontFragment = flags & 0x40;
		bool FlagIsFragmented = flags & 0x20;

		unsigned short FragmentOffset = dix->Payload->GetShortLEOrFail(6);
		FragmentOffset = ((FragmentOffset >> 8) + ((FragmentOffset & 0x1f) << 8)) << 3;

		unsigned short ID = dix->Payload->GetShortLEOrFail(4);

		unsigned char TTL = dix->Payload->GetCharOrFail(8);

		unsigned char Protocol = dix->Payload->GetCharOrFail(9);

		Protocol = dix->Payload->GetCharOrFail(9);

		PayloadQuilt payload(new CPayloadQuilt(dix->Payload, IHL32bit*4));

		std::shared_ptr<ChunkIPv4> r(new ChunkIPv4(
				dix->BaseData,
				payload,
				dix,
				IHL32bit,
				SrcIP,
				DstIP,
				PktLength,
				PayloadLength,
				Protocol,
				FlagDontFragment,
				FlagIsFragmented,
				ID,
				FragmentOffset,
				TTL));
		return (r);
	}

	return (std::shared_ptr<ChunkIPv4>(nullptr));
}
