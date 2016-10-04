
#ifndef SRC_LEVELS_PACKETIPV4_H_
#define SRC_LEVELS_PACKETIPV4_H_

#include "ChunkIPv4.h"
#include "PacketIPTraits.h"

class PacketIPv4: public Chunk<ChunkIPv4>, public PacketIPTraits {
public:
	PacketIPv4(BaseQuilt baseData
			, PayloadQuilt payload
			, std::shared_ptr<ChunkIPv4> parent);
	bool AddChunk(std::shared_ptr<ChunkIPv4> chunk);

	unsigned short int ReceivedSize;
	unsigned int ExpectedSize;
	inline char *BinaryOfSrcIP() const { return (Parent->BinaryOfSrcIP()); };
	inline char *BinaryOfDstIP() const { return (Parent->BinaryOfDstIP()); };
	inline bool CompareSrcIP(const std::shared_ptr<PacketIPTraits> &other) const {
		char *otherIPchar = other->BinaryOfSrcIP();
		unsigned long *otherIP = (unsigned long *)&otherIPchar[12];
		bool r = Parent->SrcIP == *otherIP;
		free (otherIPchar);
		return (r);
	};
};

#endif /* SRC_LEVELS_PACKETIPV4_H_ */
