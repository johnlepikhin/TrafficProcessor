
#ifndef SRC_CORE_CHUNK_H_
#define SRC_CORE_CHUNK_H_

#include <string>
#include <vector>
#include <sparsed-ropes/Quilt.h>
#include "PhantomQuilt.h"

class ChunkTraits {
public:
	ChunkTraits(BaseQuilt *baseData, PayloadQuilt *payload)
		: RefCounter(0)
		, BaseData(baseData)
		, Payload(payload) {};

	void IncrRefs(int incr);
	int DecrRefs(int decr);

	int RefCounter;

	/**
	 * Reference to original data piece
	 */
	BaseQuilt *BaseData;

	/**
	 * Reference to containing data piece
	 */
	PayloadQuilt *Payload;

};

/**
 * Base class for all types of packets
 */
template <typename PARENT>
class Chunk : public ChunkTraits {
public:
	/**
	 * Construct Chunk from Data and parent Chunk
	 * @param data Reference to original data piece
	 * @param containedData Reference to contained data piece
	 * @param parent Reference to parent Chunk
	 */
	Chunk(BaseQuilt *baseData, PayloadQuilt *payload, PARENT *parent)
		: ChunkTraits(baseData, payload)
		, Parent(parent) {}

	/**
	 * Construct Chunk from Data and NULL parent
	 * @param data Reference to data (original Pcap)
	 */
	Chunk(BaseQuilt *baseData, PayloadQuilt *payload)
		: ChunkTraits(baseData, payload)
		, Parent(NULL) {}

	virtual ~Chunk()
	{
		if (Payload)
			delete Payload;
	}

	/**
	 * Pointer to parent Chunk
	 */
	PARENT *Parent;
};

#endif /* SRC_CORE_CHUNK_H_ */
