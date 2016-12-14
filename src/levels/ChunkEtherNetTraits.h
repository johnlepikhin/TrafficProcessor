
#ifndef SRC_LEVELS_CHUNKETHERNETTRAITS_H_
#define SRC_LEVELS_CHUNKETHERNETTRAITS_H_

#include "ChunkEtherNet.h"

enum EtherNetType {
	FrameDIX,
	Frame802LLC,
	FrameSNAP,
	FrameRAW
};

class ChunkEtherNetTraits: public Chunk<ChunkEtherNet> {
public:
	ChunkEtherNetTraits(const BaseQuilt &baseData
			, const PayloadQuilt &payload
			, const std::shared_ptr<ChunkEtherNet> &parent
			, const EtherNetType frameType
			, const uint16_t protocol)
		: Chunk<ChunkEtherNet>(baseData, payload, parent)
		, FrameType(frameType)
		, TraitsProtocol(protocol)
		  {}

	EtherNetType FrameType;

	/**
	 * 2-byte value at offset 13, ethernet type (/etc/ethertypes in Debian)
	 */
	const uint16_t TraitsProtocol;
};

#endif /* SRC_LEVELS_CHUNKETHERNETTRAITS_H_ */
