
#ifndef SRC_LEVELS_PACKETIPVARIANT_H_
#define SRC_LEVELS_PACKETIPVARIANT_H_

#include <memory>
#include "PacketIPv4.h"
#include "ChunkIPv6.h"

class PacketIPVariant {
public:
	PacketIPVariant(std::shared_ptr<PacketIPv4> ipv4, std::shared_ptr<ChunkIPv6> ipv6);

	std::shared_ptr<PacketIPv4> IPv4;
	std::shared_ptr<ChunkIPv6> IPv6; // TODO: here must be PacketIPv6

	inline std::string BinaryOfSrcIP ()
	{
		if (IPv4 != nullptr) {
			return (IPv4->BinaryOfSrcIP());
		} else if (IPv6 != nullptr) {
			return (IPv6->BinaryOfSrcIP());
		}
		return ("");
	}

	inline std::string BinaryOfDstIP ()
	{
		if (IPv4 != nullptr) {
			return (IPv4->BinaryOfDstIP());
		} else if (IPv6 != nullptr) {
			return (IPv6->BinaryOfDstIP());
		}
		return ("");
	}
};

#endif /* SRC_LEVELS_PACKETIPVARIANT_H_ */
