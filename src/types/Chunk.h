
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
 * Base class for parsers of all types
 */
class Parser {
private:
	std::vector<Parser> *Followers;
public:
	/**
	 * Template for constructor of new parsers
	 */
	Parser();

	/**
	 * Base destructor for all parsers
	 */
	virtual ~Parser();

	/**
	 * Parser of chunk. Must return NULL if it was unable to detect format
	 * @param data Reference to Data
	 * @param parent Optional reference to parent Chunk
	 * @return NULL or Chunk
	 */
	virtual Chunk *DoParse(Data *data, Chunk *parent);

	/**
	 * Returns unique ID for this Parser
	 * @return ID
	 */
	virtual std::string ID();

	/**
	 * Returns description for the Parser
	 * @return Description
	 */
	virtual std::string Description();

	/**
	 * Returns reference to the vector of following parsers
	 * @return Vector of followers
	 */
	std::vector<Parser> *GetFollowers();

	/**
	 * Sets new value for vector of followers. Old vector is deleted.
	 * @param followers Reference to new vector
	 */
	void SetFollowers(std::vector<Parser> *followers);
};

#endif /* SRC_CORE_CHUNK_H_ */
