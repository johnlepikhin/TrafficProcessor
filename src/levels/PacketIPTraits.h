
#ifndef SRC_LEVELS_PACKETIPTRAITS_H_
#define SRC_LEVELS_PACKETIPTRAITS_H_

#include <memory>

class PacketIPTraits {
public:
	virtual ~PacketIPTraits() {};

	bool IsComplete;
	unsigned int RawIfaceLength;

	virtual char *BinaryOfSrcIP () const = 0;
	virtual char *BinaryOfDstIP () const = 0;
	virtual bool CompareSrcIP(const std::shared_ptr<PacketIPTraits> &other) const = 0;
};

#endif /* SRC_LEVELS_PACKETIPTRAITS_H_ */
