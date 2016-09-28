
#include "ChunkEtherNetSNAP.h"

ChunkEtherNetSNAP::ChunkEtherNetSNAP(BaseQuilt *baseData
		, PayloadQuilt *payload
		, ChunkEtherNet *parent
		, const unsigned short length
		, const unsigned int oui
		, const unsigned short pid)
	: Chunk(baseData, payload, parent)
	, PayloadLength(length)
	, OUI(oui)
	, PID(pid)
{
}
