
#ifndef SRC_LEVELS_PARSERPACKETIPV4_H_
#define SRC_LEVELS_PARSERPACKETIPV4_H_


#include <unordered_map>
#include "PacketIPVariant.h"
#include "../types/Processor.h"
#include "../types/Counter.h"

typedef unsigned int IPv4PacketID;

/**
 * Vector of IPv4 fragments
 */
class IPPacketMap : public std::vector<std::shared_ptr<PacketIPVariant> > {
public:
	/**
	 * Unique ID of the event when last fragment was received for this IP packet
	 */
	uint64_t LastInternalID; //-V122
};

/**
 * Hash table where key is srcIP+dstIP and the value is IPPacketMap
 */
class IPPairMap : public std::unordered_map<uint64_t, IPPacketMap> {
public:
	/**
	 * Register new IPv4 fragment
	 * @param chunk Pointer to IPv4 fragment
	 * @param newInternalId Unique ID of this event
	 * @return Pointer to PacketIPVariant with which this fragment is associated
	 */
	std::shared_ptr<PacketIPVariant> AddChunk(const std::shared_ptr<ChunkIPv4> &chunk
			, uint64_t newInternalId);
};

/**
 * Build IPv4 packets from IPv4 fragments
 */
class ParserPacketIPv4: public Processor<ChunkIPv4, PacketIPVariant> {
public:
	/**
	 * Collect and build IPv4 packet from chunks.
	 * @param parent Optional reference to parent Chunk
	 * @return NULL or parsed chunk
	 */
	std::shared_ptr<PacketIPVariant> Process(const std::shared_ptr<ChunkIPv4> &parent);

	/**
	 * Some post-processing after all following processors are done
	 * @param chunk Reference to generated chunk
	 * @param exn Optional generated exception
	 * @param found
	 */
	virtual int32_t AfterRecursionHook(const std::shared_ptr<PacketIPVariant> &chunk, const std::exception *exn, int32_t followersProcessed);

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

	/**
	 * Cleanup unused data. Normally there is no need to call it manually.
	 */
	void GarbageCollector();

private:
	IPPairMap IPCollector;
	uint64_t DeleteInactiveAfter = 10000; //-V122
	Counter IDGenerator;
};

#endif /* SRC_LEVELS_PARSERPACKETIPV4_H_ */
