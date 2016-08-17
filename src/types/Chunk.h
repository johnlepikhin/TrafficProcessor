
#ifndef SRC_CORE_CHUNK_H_
#define SRC_CORE_CHUNK_H_

#include <string>
#include <vector>
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
	Chunk(const Data * const data, Chunk *parent);

	/**
	 * Construct Chunk from Data and NULL parent
	 * @param data Reference to data (original Pcap)
	 */
	Chunk(const Data *data);

	/**
	 * Reference to original Pcap
	 */
	const Data *DataPtr;

	/**
	 * Pointer to position in Data where Chunk begins
	 */
	unsigned long DataPosition;

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
	std::vector<Processor> *Followers;
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
	 * Parser of chunk. Must return NULL if it was unable to detect format
	 * @param data Reference to Data
	 * @param parent Optional reference to parent Chunk
	 * @return NULL or Chunk
	 */
	virtual Chunk *DoParse(Data *data, Chunk *parent);

	/**
	 * Returns unique ID for this Processor
	 * @return ID
	 */
	virtual std::string ID();

	/**
	 * Returns description for the Processor
	 * @return Description
	 */
	virtual std::string Description();

	/**
	 * Returns reference to the vector of following processors
	 * @return Vector of followers
	 */
	std::vector<Processor> *GetFollowers();

	/**
	 * Sets new value for vector of followers. Old vector is deleted.
	 * @param followers Reference to new vector
	 */
	void SetFollowers(std::vector<Processor> *followers);
};

#endif /* SRC_CORE_CHUNK_H_ */
