
#ifndef SRC_LEVELS_PACKETIPTRAITS_H_
#define SRC_LEVELS_PACKETIPTRAITS_H_

#include <memory>
#include "ChunkIPTraits.h"
#include "../types/PhantomQuilt.h"

class PacketIPTraits {
public:
	virtual ~PacketIPTraits() {};

	bool IsComplete;
	unsigned int RawIfaceLength;
	unsigned int ExpectedSize;

	std::shared_ptr<ChunkIPTraits> IPChunk;
	PayloadQuilt IPPayload;
	BaseQuilt IPBaseData;

	virtual std::string BinaryOfSrcIP () const = 0;
	virtual std::string BinaryOfDstIP () const = 0;
//	virtual bool CompareSrcIP(const std::shared_ptr<PacketIPTraits> &other) const = 0;
};

#endif /* SRC_LEVELS_PACKETIPTRAITS_H_ */