
#ifndef SRC_LEVELS_CHUNKTCP_H_
#define SRC_LEVELS_CHUNKTCP_H_

#include "../types/Chunk.h"
#include "PacketIPVariant.h"

/**
 * Representation of TCP fragment
 */
class ChunkTCP: public Chunk<PacketIPVariant> {
public:
	/**
	 * Constructor
	 * @param baseData Reference to Data from where chunk was read
	 * @param payload Reference to payload of this frame
	 * @param parent Reference to parent Chunk
	 * @param pktLength Length of TCP fragment
	 * @param headerLength Length of TCP header
	 * @param payloadLength Length of payload
	 * @param flags Flags
	 * @param windowSize Window size
	 * @param seqNumber SEQ number
	 * @param confirmNumber ACK number
	 * @param sourcePort Source TCP port
	 * @param destinationPort Destination TCP port
	 */
	ChunkTCP(const BaseQuilt &baseData
			, const PayloadQuilt &payload
			, const std::shared_ptr<PacketIPVariant> &parent
			, const uint16_t pktLength
			, const uint16_t headerLength
			, const uint16_t payloadLength
			, const uint8_t flags
			, const uint16_t windowSize
			, const uint32_t seqNumber
			, const uint32_t confirmNumber
			, const uint16_t sourcePort
			, const uint16_t destinationPort);

	/**
	 * Length of TCP fragment
	 */
	uint16_t PktLength;

	/**
	 * Length of TCP header
	 */
	uint16_t HeaderLength;

	/**
	 * Length of payload
	 */
	uint16_t PayloadLength;

	/**
	 * TCP source port of fragment
	 */
	uint16_t SourcePort;

	/**
	 * TCP destination port of fragment
	 */
	uint16_t DestinationPort;

	/**
	 * Flag URG
	 */
	bool FlagURG;

	/**
	 * Flag ACK
	 */
	bool FlagACK;

	/**
	 * Flag PSH
	 */
	bool FlagPSH;

	/**
	 * Flag RST
	 */
	bool FlagRST;

	/**
	 * Flag SYN
	 */
	bool FlagSYN;

	/**
	 * Flag FIN
	 */
	bool FlagFIN;

	/**
	 * Window size
	 */
	uint16_t WindowSize;

	/**
	 * Sequence number
	 */
	uint32_t SeqNumber;

	/**
	 * Acknowledgment number
	 */
	uint32_t ConfirmNumber;
};

#endif /* SRC_LEVELS_CHUNKTCP_H_ */
