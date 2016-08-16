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

class ChunkEtherNet : public Chunk {
public:
	ChunkEtherNet(Data *data,
			const MAC * const destinationMAC,
			const MAC * const sourceMAC,
			const unsigned short ethernetType);

	const MAC * const DestinationMAC;
	const MAC * const SourceMAC;
	const unsigned short EtherNetType;
};

#endif /* SRC_LEVELS_CHUNKETHERNET_H_ */
