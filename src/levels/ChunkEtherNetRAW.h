
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
	 * @param dataPosition Offset of chunk beginning in Data
	 * @param parent Optional reference to parent Chunk
	 * @param length Length of payload
	 */
	ChunkEtherNetRAW(Data *data
			, const unsigned long dataPosition
			, ChunkEtherNet *parent
			, const unsigned short length);

	/**
	 * Length of payload
	 */
	const unsigned short PayloadLength;
};

#endif /* SRC_LEVELS_CHUNKETHERNETRAW_H_ */