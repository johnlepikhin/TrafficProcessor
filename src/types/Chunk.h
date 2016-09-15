
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
	Chunk(const Quilt *data, const Quilt *containedData, const Chunk *parent);

	/**
	 * Construct Chunk from Data and NULL parent
	 * @param data Reference to data (original Pcap)
	 */
	Chunk(const Quilt *data, const Quilt *containedData);

	virtual ~Chunk();

	/**
	 * Reference to original data piece
	 */
	const Quilt *Data;

	/**
	 * Reference to containing data piece
	 */
	const Quilt *ContainedData;

	/**
	 * Pointer to parent Chunk
	 */
	const Chunk *Parent;
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
	void Recursive(const Quilt *data, const Chunk *parent);

	/**
	 * Parser of chunk. Must return NULL if it was unable to detect format
	 * @param data Reference to Data
	 * @param parent Optional reference to parent Chunk
	 * @return NULL or Chunk
	 */
	virtual Chunk *Process(const Quilt *data, const Chunk *parent) = 0;

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
