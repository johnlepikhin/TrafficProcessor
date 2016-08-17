
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
	 * @param dataPosition Offset of chunk beginning in Data
	 * @param parent Optional reference to parent Chunk
	 * @param etherType EtherNet type (OSI level 3 type)
	 */
	ChunkEtherNetDIX(Data *data
			, const unsigned long dataPosition
			, ChunkEtherNet *parent
			, const unsigned short etherType);

	/**
	 * 2-byte value at offset 13, ethernet type (/etc/ethertypes in Debian)
	 */
	const unsigned short EtherNetType;
};

#endif /* SRC_LEVELS_CHUNKETHERNETDIX_H_ */
