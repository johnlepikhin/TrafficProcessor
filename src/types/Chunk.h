
#ifndef SRC_CORE_CHUNK_H_
#define SRC_CORE_CHUNK_H_

#include <string>
#include <vector>
#include <sparsed-ropes/Quilt.h>

/**
 * Base class for all types of packets
 */
class Chunk {
public:
	/**
	 * Construct Chunk from Data and parent Chunk
	 * @param data Reference to original data piece
	 * @param containedData Reference to contained data piece
	 * @param parent Reference to parent Chunk
	 */
	Chunk(Quilt *data, Quilt *containedData, const Chunk *parent);

	/**
	 * Construct Chunk from Data and NULL parent
	 * @param data Reference to data (original Pcap)
	 */
	Chunk(Quilt *data, Quilt *containedData);

	virtual ~Chunk();

	void IncrRefs(int incr);
	int DecrRefs(int decr);

	/**
	 * Reference to original data piece
	 */
	Quilt *Data;

	/**
	 * Reference to containing data piece
	 */
	Quilt *ContainedData;

	/**
	 * Pointer to parent Chunk
	 */
	const Chunk *Parent;

	int RefCounter;
};

/**
 * Base class for processors of all types
 */
class Processor {
private:
	std::vector<Processor *> Followers;
public:
	/**
	 * Template for constructor of new processors
	 */
	Processor();

	/**
	 * Base destructor for all processors
	 */
	virtual ~Processor();

	/**
	 * Call Process() and all followers recursively
	 * @param data
	 * @param parent
	 */
	void Recursive(Quilt *data, Chunk *parent);

	/**
	 * Parser of chunk. Must return NULL if it was unable to detect format
	 * @param data Reference to Data
	 * @param parent Optional reference to parent Chunk
	 * @return NULL or Chunk
	 */
	virtual Chunk *Process(Quilt *data, Chunk *parent) = 0;

	virtual void DestroyChunk(Chunk *);

	/**
	 * Returns unique ID for this Processor
	 * @return ID
	 */
	virtual std::string ID() = 0;

	/**
	 * Returns description for the Processor
	 * @return Description
	 */
	virtual std::string Description() = 0;


	/**
	 * Add follower for this processor
	 * @param follower
	 */
	void AddFollower(Processor *follower);

	/**
	 * Returns reference to the vector of following processors
	 * @return Vector of followers
	 */
	const std::vector<Processor *> &GetFollowers() const;

	/**
	 * Sets new value for vector of followers. Old vector is deleted.
	 * @param followers Reference to new vector
	 */
	void SetFollowers(std::vector<Processor *> &followers);
};

#endif /* SRC_CORE_CHUNK_H_ */
