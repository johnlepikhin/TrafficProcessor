
#ifndef SRC_LEVELS_CHUNKTCP_H_
#define SRC_LEVELS_CHUNKTCP_H_

#include "../types/Chunk.h"
#include "PacketIPVariant.h"

class ChunkTCP: public Chunk<PacketIPVariant> {
public:
	ChunkTCP(BaseQuilt baseData
			, PayloadQuilt payload
			, std::shared_ptr<PacketIPVariant> parent
			, const uint16_t pktLength
			, const uint16_t headerLength
			, const uint16_t payloadLength
			, const uint8_t flags
			, const uint16_t windowSize
			, const uint32_t seqNumber
			, const uint32_t confirmNumber
			, const uint16_t sourcePort
			, const uint16_t destinationPort);

	uint16_t PktLength;

	uint16_t HeaderLength;

	uint16_t PayloadLength;

	uint16_t SourcePort;

	uint16_t DestinationPort;

	bool FlagURG, FlagACK, FlagPSH, FlagRST, FlagSYN, FlagFIN;

	uint16_t WindowSize;

	uint32_t SeqNumber;

	uint32_t ConfirmNumber;
};

#endif /* SRC_LEVELS_CHUNKTCP_H_ */
