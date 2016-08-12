
#ifndef SRC_CORE_CHUNK_H_
#define SRC_CORE_CHUNK_H_

#include "Data.h"

/**
 * Base class for all types of packets
 */
class Chunk {
public:
	/**
	 * Construct Chunk from Data and parent Chunk
	 * @param data Reference to data (original Pcap)
	 * @param parent Reference to parent Chunk
	 */
	Chunk(Data *data, Chunk *parent);

	/**
	 * Construct Chunk from Data and NULL parent
	 * @param data Reference to data (original Pcap)
	 */
	Chunk(Data *data);

	/**
	 * Reference to original Pcap
	 */
	Data *DataPtr;

	/**
	 * Pointer to position in Data where Chunk begins
	 */
	unsigned long DataPosition;

	/**
	 * Pointer to parent Chunk
	 */
	Chunk *Parent;
};

#endif /* SRC_CORE_CHUNK_H_ */
