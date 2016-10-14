
#include "PacketIPVariant.h"

PacketIPVariant::PacketIPVariant(std::shared_ptr<PacketIPv4> ipv4, std::shared_ptr<ChunkIPv6> ipv6)
	: IPv4(ipv4)
	, IPv6(ipv6)
{
}
