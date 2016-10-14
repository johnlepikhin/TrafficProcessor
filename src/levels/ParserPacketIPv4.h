
#ifndef SRC_LEVELS_PARSERPACKETIPV4_H_
#define SRC_LEVELS_PARSERPACKETIPV4_H_


#include <unordered_map>
#include "PacketIPVariant.h"
#include "../types/Processor.h"
#include "../types/Counter.h"

typedef unsigned int IPv4PacketID;

class IPPacketMap : public std::vector<std::shared_ptr<PacketIPVariant> > {
public:
	unsigned long long LastInternalID;
};

class IPPairMap : public std::unordered_map<unsigned long long, std::shared_ptr<IPPacketMap> > {
public:
	std::shared_ptr<PacketIPVariant> AddChunk(std::shared_ptr<ChunkIPv4> chunk
			, unsigned long long newInternalId);
};

class ParserPacketIPv4: public Processor<ChunkIPv4, PacketIPVariant> {
public:
	/**
	 * Collect and build IPv4 packet from chunks.
	 * @param data Reference to Data from where chunk was read
	 * @param parent Optional reference to parent Chunk
	 * @return NULL or parsed chunk
	 */
	std::shared_ptr<PacketIPVariant> Process(std::shared_ptr<ChunkIPv4> parent);

	void AfterRecursionHook(std::shared_ptr<PacketIPVariant> chunk, std::exception *exn, bool found);

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

	void GarbageCollector();

private:
	IPPairMap IPCollector;
	unsigned long long DeleteInactiveAfter = 10000;
	Counter IDGenerator;
};

#endif /* SRC_LEVELS_PARSERPACKETIPV4_H_ */
