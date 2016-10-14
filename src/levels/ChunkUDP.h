
#ifndef SRC_LEVELS_CHUNKUDP_H_
#define SRC_LEVELS_CHUNKUDP_H_

#include "../types/Chunk.h"
#include "PacketIPVariant.h"

class ChunkUDP: public Chunk<PacketIPVariant> {
public:
	ChunkUDP(BaseQuilt baseData
			, PayloadQuilt payload
			, std::shared_ptr<PacketIPVariant> parent
			, const unsigned int pktLength
			, const unsigned int payloadLength
			, const unsigned int sourcePort
			, const unsigned int destinationPort);

	unsigned int PktLength;

	unsigned int PayloadLength;

	unsigned int SourcePort;

	unsigned int DestinationPort;
};

#endif /* SRC_LEVELS_CHUNKUDP_H_ */
