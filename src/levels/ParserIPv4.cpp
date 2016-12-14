// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

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

std::shared_ptr<ChunkIPv4> ParserIPv4::Process(const std::shared_ptr<ChunkEtherNetTraits> &dix)
{
	if (dix->Parent->EtherNetType == 0x800) {
		unsigned char IHL32bit = dix->Payload->GetCharOrFail(0) & 0xf;

		uint32_t SrcIP = IPv4Addr::Make(*dix->Payload, 12);
		uint32_t DstIP = IPv4Addr::Make(*dix->Payload, 16);

		uint16_t PktLength = dix->Payload->GetShortLEOrFail(2);
		PktLength = static_cast<uint16_t>((PktLength>>8) | (PktLength<<8));

		uint16_t PayloadLength = PktLength - IHL32bit*4; //-V112

		unsigned char flags = dix->Payload->GetCharOrFail(6);
		bool FlagDontFragment = flags & 0x40;
		bool FlagIsFragmented = flags & 0x20;

		unsigned short FragmentOffset = dix->Payload->GetShortLEOrFail(6);
		FragmentOffset = ((FragmentOffset >> 8) + ((FragmentOffset & 0x1f) << 8)) << 3;

		uint16_t ID = dix->Payload->GetShortLEOrFail(4); //-V112

		unsigned char TTL = dix->Payload->GetCharOrFail(8);

		unsigned char Protocol = dix->Payload->GetCharOrFail(9);

		PayloadQuilt payload = std::make_shared<CPayloadQuilt>(dix->Payload, IHL32bit*4); //-V112

		std::shared_ptr<ChunkIPv4> r = std::make_shared<ChunkIPv4>(
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
				TTL);
		return (r);
	}

	return (std::shared_ptr<ChunkIPv4>(nullptr));
}
