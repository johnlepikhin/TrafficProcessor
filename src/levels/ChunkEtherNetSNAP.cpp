
#include "ChunkEtherNetSNAP.h"

ChunkEtherNetSNAP::ChunkEtherNetSNAP(Data *data
		, const unsigned long dataPosition
		, ChunkEtherNet *parent
		, const unsigned short length
		, const unsigned int oui
		, const unsigned short pid)
	: Chunk(data, dataPosition, parent)
	, PayloadLength(length)
	, OUI(oui)
	, PID(pid)
{
}
