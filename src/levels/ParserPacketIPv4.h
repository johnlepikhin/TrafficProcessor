
#ifndef SRC_LEVELS_PARSERPACKETIPV4_H_
#define SRC_LEVELS_PARSERPACKETIPV4_H_


#include <unordered_map>
#include "PacketIPv4.h"
#include "../types/Processor.h"

typedef unsigned int IPv4PacketID;

class IPPacketMap : public std::vector<std::shared_ptr<PacketIPv4> > {
};

class IPPairMap : public std::unordered_map<unsigned long long, std::shared_ptr<IPPacketMap> > {
public:
	std::shared_ptr<PacketIPv4> AddChunk(std::shared_ptr<ChunkIPv4> chunk);
};

class ParserPacketIPv4: public Processor<ChunkIPv4, PacketIPv4> {
public:
	/**
	 * Collect and build IPv4 packet from chunks.
	 * @param data Reference to Data from where chunk was read
	 * @param parent Optional reference to parent Chunk
	 * @return NULL or parsed chunk
	 */
	std::shared_ptr<PacketIPv4> Process(std::shared_ptr<ChunkIPv4> parent);

	void DestroyChunk(std::shared_ptr<PacketIPv4> chunk);

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
