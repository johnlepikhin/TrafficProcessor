
#ifndef SRC_LEVELS_PACKETIPV4_H_
#define SRC_LEVELS_PACKETIPV4_H_

#include "ChunkIPv4.h"

/**
 * Representation of defragmentated IPv4 packet
 */
class PacketIPv4: public Chunk<ChunkIPv4> {
public:
	/**
	 * Constructor
	 * @param baseData Reference to Data from where chunk was read
	 * @param payload Reference to payload of this frame
	 * @param parent Optional reference to parent Chunk
	 */
	PacketIPv4(const BaseQuilt &baseData
			, const PayloadQuilt &payload
			, const std::shared_ptr<ChunkIPv4> &parent);

	/**
	 * Add IPv4 fragment to the packet
	 * @param chunk IPv4 fragment
	 * @return True if all expected fragments are registered within this packet
	 */
	bool AddChunk(const std::shared_ptr<ChunkIPv4> &chunk);

	/**
	 * True if all fragments are found and packet is ready to use
	 */
	bool IsComplete;

	/**
	 * Summary payload length of all found fragments
	 */
	unsigned short int ReceivedSize;

	/**
	 * Summary raw data length of all found fragments
	 */
	unsigned int RawIfaceLength;

	/**
	 * Expected payload length of full packet
	 */
	unsigned int ExpectedSize;

	/**
	 * Get source IP as bytes
	 * @return source IP address as bytes
	 */
	inline std::string BinaryOfSrcIP() const { return (Parent->BinaryOfSrcIP()); };

	/**
	 * Get destination IP as bytes
	 * @return destination IP address as bytes
	 */
	inline std::string BinaryOfDstIP() const { return (Parent->BinaryOfDstIP()); };
};

#endif /* SRC_LEVELS_PACKETIPV4_H_ */
