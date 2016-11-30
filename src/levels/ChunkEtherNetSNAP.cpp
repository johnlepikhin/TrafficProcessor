// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "ChunkEtherNetSNAP.h"

ChunkEtherNetSNAP::ChunkEtherNetSNAP(const BaseQuilt &baseData
		, const PayloadQuilt &payload
		, const std::shared_ptr<ChunkEtherNet> &parent
		, const unsigned short length
		, const unsigned int oui
		, const unsigned short pid)
	: Chunk(baseData, payload, parent)
	, PayloadLength(length)
	, OUI(oui)
	, PID(pid)
{
}
