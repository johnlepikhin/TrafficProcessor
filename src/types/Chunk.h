
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

//	virtual ~Chunk();

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

template <class PARENT, class RETURN>
class Parser {
private:
	std::vector<Parser> Followers;
public:
	Parser();
	virtual ~Parser();
	virtual RETURN *parse(PARENT *data);
	virtual std::string ID();
	virtual std::string Description();
	std::vector<Parser> *GetFollowers();
	void SetFollowers(std::vector<Parser> *followers);
};

#endif /* SRC_CORE_CHUNK_H_ */
