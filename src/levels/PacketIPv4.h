
#ifndef SRC_LEVELS_PACKETIPV4_H_
#define SRC_LEVELS_PACKETIPV4_H_

#include "../types/Chunk.h"
#include "ChunkIPv4.h"

class PacketIPv4: public Chunk {
public:
	PacketIPv4(ChunkIPv4 *chunk);
	~PacketIPv4();
	bool AddChunk(ChunkIPv4 *chunk);

	bool IsComplete;
	unsigned short int ReceivedSize;
	unsigned int ExpectedSize;
};

#endif /* SRC_LEVELS_PACKETIPV4_H_ */
