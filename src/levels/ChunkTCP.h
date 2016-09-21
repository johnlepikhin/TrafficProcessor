
#ifndef SRC_LEVELS_CHUNKTCP_H_
#define SRC_LEVELS_CHUNKTCP_H_

#include "../types/Chunk.h"

class ChunkTCP: public Chunk {
public:
	ChunkTCP(Quilt *data
			, Quilt *containedData
			, const unsigned int pktLength
			, const unsigned int headerLength
			, const unsigned int payloadLength
			, const unsigned int sourcePort
			, const unsigned int destinationPort);

	unsigned int PktLength;

	unsigned int HeaderLength;

	unsigned int PayloadLength;

	unsigned int SourcePort;

	unsigned int DestinationPort;
};

#endif /* SRC_LEVELS_CHUNKTCP_H_ */
