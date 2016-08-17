/*
 * ChunkEtherNet.h
 *
 *  Created on: 15 авг. 2016 г.
 *      Author: eugene
 */

#ifndef SRC_LEVELS_CHUNKETHERNET_H_
#define SRC_LEVELS_CHUNKETHERNET_H_

#include "../types/Data.h"
#include "../types/Chunk.h"
#include "../types/MAC.h"

/**
 * Container for EtherNet frame
 */
class ChunkEtherNet : public Chunk {
public:
	/**
	 * Constructor
	 * @param data Reference to Data from where chunk was read
	 * @param dataPosition Offset of chunk beginning in Data
	 * @param destinationMAC Reference to destination MAC address
	 * @param sourceMAC Reference to source MAC address
	 * @param ethernetType 2-byte value at offset 13 in ethernet frame (ethernet type or payload length)
	 */
	ChunkEtherNet(Data *data,
			const unsigned long dataPosition,
			const MAC * const destinationMAC,
			const MAC * const sourceMAC,
			const unsigned short ethernetType);

	~ChunkEtherNet();

	/**
	 * Reference to destination MAC address
	 */
	const MAC * const DestinationMAC;

	/**
	 * Reference to source MAC address
	 */
	const MAC * const SourceMAC;

	/**
	 * 2-byte value at offset 13, ethernet type or payload length
	 */
	const unsigned short EtherNetType;
};

#endif /* SRC_LEVELS_CHUNKETHERNET_H_ */
