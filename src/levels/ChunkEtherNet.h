
#ifndef SRC_LEVELS_CHUNKETHERNET_H_
#define SRC_LEVELS_CHUNKETHERNET_H_

#include "../types/Data.h"
#include "../types/Chunk.h"
#include "../types/MAC.h"

/**
 * Container for EtherNet frame
 */
//lint -sem(ChunkEtherNet::ChunkEtherNet, 1p)
//lint -sem(ChunkEtherNet::ChunkEtherNet, 3p, custodial(3))
//lint -sem(ChunkEtherNet::ChunkEtherNet, 4p, custodial(4))
class ChunkEtherNet : public Chunk {
public:
	/**
	 * Constructor
	 * @param data Reference to Data from where chunk was read
	 * @param destinationMAC Reference to destination MAC address
	 * @param sourceMAC Reference to source MAC address
	 * @param ethernetType 2-byte value at offset 13 in ethernet frame (ethernet type or payload length)
	 */
	ChunkEtherNet(Quilt *data,
			Quilt *containedData,
			const MAC *destinationMAC,
			const MAC *sourceMAC,
			const unsigned short ethernetType);

	~ChunkEtherNet();

	/**
	 * Reference to destination MAC address
	 */
	const MAC *DestinationMAC;

	/**
	 * Reference to source MAC address
	 */
	const MAC *SourceMAC;

	/**
	 * 2-byte value at offset 13, ethernet type or payload length
	 */
	const unsigned short EtherNetType;
};

#endif /* SRC_LEVELS_CHUNKETHERNET_H_ */
