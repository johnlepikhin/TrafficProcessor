
#ifndef SRC_LEVELS_PACKETIPV4_H_
#define SRC_LEVELS_PACKETIPV4_H_

#include "ChunkIPv4.h"

class PacketIPv4: public Chunk<ChunkIPv4> {
public:
	PacketIPv4(BaseQuilt *baseData
			, PayloadQuilt *payload
			, ChunkIPv4 *parent);
	~PacketIPv4();
	bool AddChunk(ChunkIPv4 *chunk);

	bool IsComplete;
	unsigned short int ReceivedSize;
	unsigned int ExpectedSize;
};

#endif /* SRC_LEVELS_PACKETIPV4_H_ */
