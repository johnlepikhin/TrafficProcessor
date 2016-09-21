
#ifndef SRC_LEVELS_CHUNKETHERNETSNAP_H_
#define SRC_LEVELS_CHUNKETHERNETSNAP_H_

#include "../types/Chunk.h"
#include "ChunkEtherNet.h"

/**
 * Container for SNAP EtherNet frame
 */
class ChunkEtherNetSNAP: public Chunk {
public:
	/**
	 * Constructor for SNAP
	 * @param data Reference to Data from where chunk was read
	 * @param parent Optional reference to parent Chunk
	 * @param length Length of payload
	 * @param oui OUI
	 * @param pid PID
	 */
	ChunkEtherNetSNAP(Quilt *data
			, Quilt *containedData
			, ChunkEtherNet *parent
			, const unsigned short length
			, const unsigned int oui
			, const unsigned short pid);

	/**
	 * 2-byte length of payload
	 */
	const unsigned short PayloadLength;

	/**
	 * OUI
	 */
	const unsigned int OUI;

	/**
	 * PID
	 */
	const unsigned short PID;
};

#endif /* SRC_LEVELS_CHUNKETHERNETSNAP_H_ */
