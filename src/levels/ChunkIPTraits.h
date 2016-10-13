
#ifndef SRC_LEVELS_CHUNKIPTRAITS_H_
#define SRC_LEVELS_CHUNKIPTRAITS_H_

#include <string>
#include "ChunkEtherNetDIX.h"

class ChunkIPTraits {
public:
	ChunkIPTraits(unsigned char protocol
			, std::shared_ptr<ChunkEtherNetDIX> IPEtherNetDIX);

	/**
	 * Next protocol ID
	 */
	unsigned char Protocol;

	std::shared_ptr<ChunkEtherNetDIX> IPEtherNetDIX;

	ChunkIPTraits(unsigned char protocol);
	virtual ~ChunkIPTraits() {};

	virtual std::string StringOfSrcIP () = 0;
	virtual std::string StringOfDstIP () = 0;

	virtual std::string BinaryOfSrcIP () = 0;
	virtual std::string BinaryOfDstIP () = 0;
};

#endif /* SRC_LEVELS_CHUNKIPTRAITS_H_ */
