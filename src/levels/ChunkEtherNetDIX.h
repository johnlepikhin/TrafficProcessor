
#ifndef SRC_LEVELS_CHUNKETHERNETDIX_H_
#define SRC_LEVELS_CHUNKETHERNETDIX_H_

#include "ChunkEtherNet.h"

/**
 * Container for DIX EtherNet frame
 */
class ChunkEtherNetDIX: public Chunk {
public:
	/**
	 * Constructor for DIX
	 * @param data Reference to Data from where chunk was read
	 * @param parent Optional reference to parent Chunk
	 */
	ChunkEtherNetDIX(Data *data, ChunkEtherNet *parent);
};

#endif /* SRC_LEVELS_CHUNKETHERNETDIX_H_ */
