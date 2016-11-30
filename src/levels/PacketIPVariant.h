
#ifndef SRC_LEVELS_PACKETIPVARIANT_H_
#define SRC_LEVELS_PACKETIPVARIANT_H_

#include <memory>
#include "PacketIPv4.h"
#include "ChunkIPv6.h"

/**
 * Collective class for all types of IP protocols
 */
class PacketIPVariant {
public:
	/**
	 * Constructor
	 * @param ipv4 Optional pointer to IPv4 fragment
	 * @param ipv6 Optional pointer to IPv6 fragment
	 */
	PacketIPVariant(const std::shared_ptr<PacketIPv4> &ipv4
			, const std::shared_ptr<ChunkIPv6> &ipv6);

	/**
	 * Optional pointer to IPv4 fragment
	 */
	std::shared_ptr<PacketIPv4> IPv4;

	/**
	 * Optional pointer to IPv6 fragment
	 */
	std::shared_ptr<ChunkIPv6> IPv6; // TODO: here must be PacketIPv6

	/**
	 * Get source IP as bytes
	 * @return source IP address as bytes
	 */
	inline std::string BinaryOfSrcIP ()
	{
		if (IPv4 != nullptr) {
			return (IPv4->BinaryOfSrcIP());
		} else if (IPv6 != nullptr) {
			return (IPv6->BinaryOfSrcIP());
		}
		return ("");
	}

	/**
	 * Get destination IP as bytes
	 * @return destination IP address as bytes
	 */
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
