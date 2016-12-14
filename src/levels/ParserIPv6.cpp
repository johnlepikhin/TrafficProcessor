// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include <typeinfo>

#include "ParserIPv6.h"

std::string ParserIPv6::ID()
{
	return (std::string("IPv6_Fragment"));
}

std::string ParserIPv6::Description()
{
	return (std::string("IPv6 fragment parser"));
}

std::shared_ptr<ChunkIPv6> ParserIPv6::Process(const std::shared_ptr<ChunkEtherNetTraits> &parent)
{
	if (parent->Parent->EtherNetType == 0x86dd) {
		std::string tmp = parent->Payload->GetSubStringOrFail(0, 8);
		unsigned char version = tmp[0] >> 4;
		if (version == 6) {

			unsigned char traffic_class = (tmp[0] >> 4) & 0xff;
			uint32_t flow_label = (tmp[0] & 0xf) << 12;
			flow_label &= (tmp[1] << 8) | tmp[2];

			uint32_t payloadLength = ((static_cast<uint32_t>(tmp[4])) << 8) | tmp[5];
			unsigned char next_header = tmp[6];
			unsigned char hop_limit = tmp[7];

			IPv6Addr srcAddr(*parent->Payload, 8);
			IPv6Addr dstAddr(*parent->Payload, 0x18);

			std::shared_ptr<IPv6HeaderFragment> hdrFragment = std::make_shared<IPv6HeaderFragment>(0, false, 0);

			uint32_t hdrOffset = 0x28;

			while (next_header == 0
					|| next_header == 60
					|| next_header == 43
					|| next_header == 44
					|| next_header == 50
					|| next_header == 51) {
				unsigned short tmp_short = parent->Payload->GetShortLEOrFail(hdrOffset);
				next_header = tmp_short >> 8;

				switch (next_header) {
				case 0: // Hop-by-Hop Options
				{
					std::cout << "hop-by-hop detected\n";

					uint32_t hdrExtLen = (tmp_short & 0xff) << 3;
					uint32_t optOffset = 2;
					while (optOffset < hdrExtLen) {
						tmp_short = parent->Payload->GetShortLEOrFail(optOffset);
						unsigned char opt_type = tmp_short >> 8;
						unsigned char opt_len = tmp_short & 0xff;

						switch (opt_type) {

						case 0xc2: // Jumbogram
							parent->Payload->CopyBytesOrFail(
									reinterpret_cast<char *>(&payloadLength) //-V206
									, optOffset+2, 4); //-V112
							break;

						default:
							break;
						}

						optOffset+=2+opt_len;
					}

					hdrOffset += 4 + ((tmp_short & 0xff) << 3); //-V112
					break;
				}
				case 43: // Routing
				case 60: // Destination
					hdrOffset += 4 + ((tmp_short & 0xff) << 3); //-V112
					break;

				case 44: // Fragment
				{
					tmp_short = parent->Payload->GetShortLEOrFail(hdrOffset+2);
					uint32_t fragment_offset = (tmp_short >> 3) << 3;
					bool has_next_fragments = tmp_short & 1;
					uint32_t packetID = 0;
					parent->Payload->CopyBytesOrFail(
							reinterpret_cast<char *>(&packetID) //-V206
							, hdrOffset+4, 4); //-V112

					std::shared_ptr<IPv6HeaderFragment> newHdrFragment
						= std::make_shared<IPv6HeaderFragment>(fragment_offset, has_next_fragments, packetID);
					hdrFragment = newHdrFragment;

					hdrOffset += 8;

					break;
				}
				case 50:
				case 51:
				default:
					// TODO
					return (std::shared_ptr<ChunkIPv6>(nullptr));
				}
			}

			payloadLength = payloadLength + 0x28 - hdrOffset;

			PayloadQuilt payload(new CPayloadQuilt(parent->Payload, hdrOffset));

			return (std::make_shared<ChunkIPv6>(parent->BaseData
					, payload
					, parent
					, srcAddr
					, dstAddr
					, next_header
					, traffic_class
					, flow_label
					, hop_limit
					, hdrFragment
					, payloadLength));
		}
	}

	return (std::shared_ptr<ChunkIPv6>(nullptr));
}
