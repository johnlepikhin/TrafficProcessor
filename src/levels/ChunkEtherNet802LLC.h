
#ifndef SRC_LEVELS_CHUNKETHERNET802LLC_H_
#define SRC_LEVELS_CHUNKETHERNET802LLC_H_

#include "../types/Chunk.h"
#include "ChunkEtherNetTraits.h"

/**
 * Container for 802.3 LLC EtherNet frame
 */
class ChunkEtherNet802LLC : public ChunkEtherNetTraits {
public:
	/**
	 * Constructor for 802.3 LLC
	 * @param baseData Reference to Data from where chunk was read
	 * @param payload Reference to payload of this frame
	 * @param parent Optional reference to parent Chunk
	 * @param length Length of payload
	 * @param dsap Destination Service Access Point
	 * @param ssap Source Service Access Point
	 * @param control Control
	 */
	ChunkEtherNet802LLC(const BaseQuilt &baseData
			, const PayloadQuilt &payload
			, const std::shared_ptr<ChunkEtherNet> &parent
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
