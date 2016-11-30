
#ifndef SRC_LEVELS_CHUNKETHERNET_H_
#define SRC_LEVELS_CHUNKETHERNET_H_

#include "ChunkRaw.h"
#include "../types/MAC.h"

/**
 * Container for EtherNet frame
 */
//lint -sem(ChunkEtherNet::ChunkEtherNet, 1p)
//lint -sem(ChunkEtherNet::ChunkEtherNet, 3p, custodial(3))
//lint -sem(ChunkEtherNet::ChunkEtherNet, 4p, custodial(4))
class ChunkEtherNet : public Chunk<CBaseQuilt> {
public:
	/**
	 * Constructor
	 * @param baseData Reference to Data from where chunk was read
	 * @param payload Reference to payload of this frame
	 * @param destinationMAC Reference to destination MAC address
	 * @param sourceMAC Reference to source MAC address
	 * @param ethernetType 2-byte value at offset 13 in ethernet frame (ethernet type or payload length)
	 */
	ChunkEtherNet(const BaseQuilt &baseData,
			const PayloadQuilt &payload,
			const unsigned long long destinationMAC,
			const unsigned long long sourceMAC,
			const unsigned short ethernetType);

	/**
	 * Reference to destination MAC address
	 */
	const unsigned long long DestinationMAC;

	/**
	 * Reference to source MAC address
	 */
	const unsigned long long SourceMAC;

	/**
	 * 2-byte value at offset 13, ethernet type or payload length
	 */
	const unsigned short EtherNetType;
};

#endif /* SRC_LEVELS_CHUNKETHERNET_H_ */
