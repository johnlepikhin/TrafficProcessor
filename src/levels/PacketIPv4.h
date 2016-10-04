
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
	inline std::string BinaryOfSrcIP() const { return (Parent->BinaryOfSrcIP()); };
	inline std::string BinaryOfDstIP() const { return (Parent->BinaryOfDstIP()); };
//	inline bool CompareSrcIP(const std::shared_ptr<PacketIPTraits> &other) const {
//		std::string otherIPchar = other->BinaryOfSrcIP();
//		unsigned long *otherIP = (unsigned long *)&otherIPchar[12];
//		bool r = Parent->SrcIP == *otherIP;
//		return (r);
//	};
};

#endif /* SRC_LEVELS_PACKETIPV4_H_ */
