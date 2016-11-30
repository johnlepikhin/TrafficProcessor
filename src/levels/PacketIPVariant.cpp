// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "PacketIPVariant.h"

PacketIPVariant::PacketIPVariant(const std::shared_ptr<PacketIPv4> &ipv4
		, const std::shared_ptr<ChunkIPv6> &ipv6)
	: IPv4(ipv4)
	, IPv6(ipv6)
{
}
