
#ifndef SRC_CORE_CHUNK_H_
#define SRC_CORE_CHUNK_H_

#include <string>
#include <vector>
#include <memory>
#include <sparsed-ropes/Quilt.h>
#include "PhantomQuilt.h"

/**
 * Base traits for chunks of all levels and protocols
 */
class ChunkTraits {
public:
	/**
	 * Construct traits
	 * @param baseData Reference to original data chunk
	 * @param payload Reference to payload
	 */
	ChunkTraits(const BaseQuilt &baseData, const PayloadQuilt &payload)
		: BaseData(baseData)
		, Payload(payload) {};

	/**
	 * Reference to original data piece
	 */
	BaseQuilt BaseData;

	/**
	 * Reference to containing data piece
	 */
	PayloadQuilt Payload;

};

/**
 * Base class for all types of packets
 */
template <typename PARENT>
class Chunk : public ChunkTraits {
public:
	/**
	 * Construct Chunk from Data and parent Chunk
	 * @param baseData Reference to original data piece
	 * @param payload Reference to contained data piece
	 * @param parent Reference to parent Chunk
	 */
	Chunk(const BaseQuilt &baseData, const PayloadQuilt &payload, const std::shared_ptr<PARENT> &parent)
		: ChunkTraits(baseData, payload)
		, Parent(parent) {}

	/**
	 * Construct Chunk from Data and NULL parent
	 * @param baseData Reference to original data piece
	 * @param payload Reference to contained data piece
	 */
	Chunk(const BaseQuilt &baseData, const PayloadQuilt &payload)
		: ChunkTraits(baseData, payload)
		, Parent(std::shared_ptr<PARENT>(nullptr)) {}

	/**
	 * Pointer to parent Chunk
	 */
	std::shared_ptr<PARENT> Parent;
};

#endif /* SRC_CORE_CHUNK_H_ */
