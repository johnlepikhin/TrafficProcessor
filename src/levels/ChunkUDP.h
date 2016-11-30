
#ifndef SRC_LEVELS_CHUNKUDP_H_
#define SRC_LEVELS_CHUNKUDP_H_

#include "../types/Chunk.h"
#include "PacketIPVariant.h"

/**
 * Representation of UDP datagrams
 */
class ChunkUDP: public Chunk<PacketIPVariant> {
public:
	/**
	 * Constructor
	 * @param baseData Reference to Data from where chunk was read
	 * @param payload Reference to payload of this frame
	 * @param parent Optional reference to parent Chunk
	 * @param pktLength Full packet length
	 * @param payloadLength Payload length
	 * @param sourcePort Source UDP port
	 * @param destinationPort Destination UDP port
	 */
	ChunkUDP(const BaseQuilt &baseData
			, const PayloadQuilt &payload
			, const std::shared_ptr<PacketIPVariant> &parent
			, const unsigned int pktLength
			, const unsigned int payloadLength
			, const unsigned int sourcePort
			, const unsigned int destinationPort);

	/**
	 * Full datagram length
	 */
	unsigned int PktLength;

	/**
	 * Payload length
	 */
	unsigned int PayloadLength;

	/**
	 * Source UDP port
	 */
	unsigned int SourcePort;

	/**
	 * Destination UDP port
	 */
	unsigned int DestinationPort;
};

#endif /* SRC_LEVELS_CHUNKUDP_H_ */
