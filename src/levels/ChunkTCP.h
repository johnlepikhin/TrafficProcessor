
#ifndef SRC_LEVELS_CHUNKTCP_H_
#define SRC_LEVELS_CHUNKTCP_H_

#include "../types/Chunk.h"
#include "PacketIPTraits.h"

class ChunkTCP: public Chunk<PacketIPTraits> {
public:
	ChunkTCP(BaseQuilt baseData
			, PayloadQuilt payload
			, std::shared_ptr<PacketIPTraits> parent
			, const unsigned int pktLength
			, const unsigned int headerLength
			, const unsigned int payloadLength
			, const unsigned char flags
			, const unsigned short windowSize
			, const unsigned long seqNumber
			, const unsigned long confirmNumber
			, const unsigned int sourcePort
			, const unsigned int destinationPort);

	unsigned int PktLength;

	unsigned int HeaderLength;

	unsigned int PayloadLength;

	unsigned int SourcePort;

	unsigned int DestinationPort;

	bool FlagURG, FlagACK, FlagPSH, FlagRST, FlagSYN, FlagFIN;

	unsigned short WindowSize;

	unsigned long SeqNumber;

	unsigned long ConfirmNumber;
};

#endif /* SRC_LEVELS_CHUNKTCP_H_ */
