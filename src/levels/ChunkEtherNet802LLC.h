
#ifndef SRC_LEVELS_CHUNKETHERNET802LLC_H_
#define SRC_LEVELS_CHUNKETHERNET802LLC_H_

#include "../types/Chunk.h"
#include "ChunkEtherNet.h"

/**
 * Container for 802.3 LLC EtherNet frame
 */
class ChunkEtherNet802LLC : public Chunk {
public:
	/**
	 * Constructor for 802.3 LLC
	 * @param data Reference to Data from where chunk was read
	 * @param dataPosition Offset of chunk beginning in Data
	 * @param parent Optional reference to parent Chunk
	 * @param length Length of payload
	 * @param dsap Destination Service Access Point
	 * @param ssap Source Service Access Point
	 * @param control Control
	 */
	ChunkEtherNet802LLC(Data *data
			, const unsigned long dataPosition
			, ChunkEtherNet *parent
			, const unsigned short length
			, const unsigned char dsap
			, const unsigned char ssap
			, const unsigned char control);

	/**
	 * 2-byte length of payload
	 */
	const unsigned short PayloadLength;

	/**
	 * Destination Service Access Point
	 */
	const unsigned char DSAP;

	/**
	 * Source Service Access Point
	 */
	const unsigned char SSAP;

	/**
	 * Control
	 */
	const unsigned char Control;
};

#endif /* SRC_LEVELS_CHUNKETHERNETSNAP_H_ */
