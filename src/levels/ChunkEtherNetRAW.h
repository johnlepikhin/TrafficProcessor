
#ifndef SRC_LEVELS_CHUNKETHERNETRAW_H_
#define SRC_LEVELS_CHUNKETHERNETRAW_H_

#include "../types/Chunk.h"
#include "ChunkEtherNet.h"

/**
 * Container for RAW EtherNet frame
 */
class ChunkEtherNetRAW: public Chunk {
public:
	/**
	 * Constructor for RAW
	 * @param data Reference to Data from where chunk was read
	 * @param parent Optional reference to parent Chunk
	 * @param length Length of payload
	 */
	ChunkEtherNetRAW(const Quilt *data
			, const Quilt *containedData
			, const ChunkEtherNet *parent
			, const unsigned short length);

	/**
	 * Length of payload
	 */
	const unsigned short PayloadLength;
};

#endif /* SRC_LEVELS_CHUNKETHERNETRAW_H_ */
