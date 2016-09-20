
#ifndef SRC_LEVELS_PARSERPACKETIPV4_H_
#define SRC_LEVELS_PARSERPACKETIPV4_H_


#include <unordered_map>
#include "PacketIPv4.h"

typedef int IPv4PacketID;

class IPPacketMap : public std::unordered_map<IPv4PacketID, PacketIPv4 *> {
};

class IPPairMap : public std::unordered_map<unsigned long long, IPPacketMap *> {
public:
	PacketIPv4 *AddChunk(ChunkIPv4 *chunk);
};

class ParserPacketIPv4: public Processor {
public:
	~ParserPacketIPv4();

	/**
	 * Collect and build IPv4 packet from chunks.
	 * @param data Reference to Data from where chunk was read
	 * @param parent Optional reference to parent Chunk
	 * @return NULL or parsed chunk
	 */
	PacketIPv4 *Process(Quilt *data, Chunk *parent);

	void DestroyChunk(Chunk *chunk);

	/**
	 * Returns unique ID for this Parser
	 * @return ID
	 */
	std::string ID();

	/**
	 * Returns description for this Parser
	 * @return Description
	 */
	std::string Description();


private:
	IPPairMap IPCollector;
};

#endif /* SRC_LEVELS_PARSERPACKETIPV4_H_ */
