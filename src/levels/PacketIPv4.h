
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
	unsigned int RawIfaceLength;
	unsigned int ExpectedSize;

	inline std::string BinaryOfSrcIP() const { return (Parent->BinaryOfSrcIP()); };
	inline std::string BinaryOfDstIP() const { return (Parent->BinaryOfDstIP()); };
};

#endif /* SRC_LEVELS_PACKETIPV4_H_ */
