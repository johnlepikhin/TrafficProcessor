
#ifndef SRC_LEVELS_CHUNKIPTRAITS_H_
#define SRC_LEVELS_CHUNKIPTRAITS_H_

#include <string>

class ChunkIPTraits {
public:
	/**
	 * Next protocol ID
	 */
	unsigned char Protocol;

	ChunkIPTraits(unsigned char protocol);
	virtual ~ChunkIPTraits() {};

	virtual std::string StringOfSrcIP () = 0;
	virtual std::string StringOfDstIP () = 0;

	virtual char *BinaryOfSrcIP () = 0;
	virtual char *BinaryOfDstIP () = 0;
};

#endif /* SRC_LEVELS_CHUNKIPTRAITS_H_ */
