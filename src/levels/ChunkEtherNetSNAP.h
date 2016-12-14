
#ifndef SRC_LEVELS_CHUNKETHERNETSNAP_H_
#define SRC_LEVELS_CHUNKETHERNETSNAP_H_

#include "../types/Chunk.h"
#include "ChunkEtherNet802LLC.h"

/**
 * Container for SNAP EtherNet frame
 */
class ChunkEtherNetSNAP: public ChunkEtherNet802LLC {
public:
	/**
	 * Constructor for SNAP
	 * @param baseData Reference to Data from where chunk was read
	 * @param payload Reference to payload of this frame
	 * @param parent Optional reference to parent Chunk
	 * @param length Length of payload
	 * @param oui OUI
	 * @param pid PID
	 */
	ChunkEtherNetSNAP(const BaseQuilt &baseData
			, const PayloadQuilt &payload
			, const std::shared_ptr<ChunkEtherNet> &parent
			, const uint16_t length
			, const uint8_t dsap
			, const uint8_t ssap
			, const uint8_t control
			, const uint32_t oui
			, const uint16_t pid);

	/**
	 * OUI
	 */
	const uint32_t OUI;

	/**
	 * PID
	 */
	const uint16_t PID;
};

#endif /* SRC_LEVELS_CHUNKETHERNETSNAP_H_ */
