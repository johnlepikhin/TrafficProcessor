
#ifndef SRC_LEVELS_PACKETIPV4_H_
#define SRC_LEVELS_PACKETIPV4_H_

#include "ChunkIPv4.h"

class PacketIPv4: public Chunk<ChunkIPv4> {
public:
	PacketIPv4(BaseQuilt baseData
			, PayloadQuilt payload
			, std::shared_ptr<ChunkIPv4> parent);
	bool AddChunk(std::shared_ptr<ChunkIPv4> chunk);

	bool IsComplete;
	unsigned short int ReceivedSize;
	unsigned int ExpectedSize;

	unsigned int IFaceSize;
};

#endif /* SRC_LEVELS_PACKETIPV4_H_ */
