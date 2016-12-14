// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "ChunkEtherNetSNAP.h"

ChunkEtherNetSNAP::ChunkEtherNetSNAP(const BaseQuilt &baseData
		, const PayloadQuilt &payload
		, const std::shared_ptr<ChunkEtherNet> &parent
		, const uint16_t length
		, const uint8_t dsap
		, const uint8_t ssap
		, const uint8_t control
		, const uint32_t oui
		, const uint16_t pid)
	: ChunkEtherNet802LLC(baseData, payload, parent, length, dsap, ssap, control)
	, OUI(oui)
	, PID(pid)
{
}
