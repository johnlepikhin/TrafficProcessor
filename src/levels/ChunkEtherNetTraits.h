
#ifndef SRC_LEVELS_CHUNKETHERNETTRAITS_H_
#define SRC_LEVELS_CHUNKETHERNETTRAITS_H_

#include "ChunkEtherNet.h"

class ChunkEtherNetTraits: public Chunk<ChunkEtherNet> {
public:
	ChunkEtherNetTraits(const BaseQuilt &baseData
			, const PayloadQuilt &payload
			, const std::shared_ptr<ChunkEtherNet> &parent)
		: Chunk<ChunkEtherNet>(baseData, payload, parent) {}
};

#endif /* SRC_LEVELS_CHUNKETHERNETTRAITS_H_ */
