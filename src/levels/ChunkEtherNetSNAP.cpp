
#include "ChunkEtherNetSNAP.h"

ChunkEtherNetSNAP::ChunkEtherNetSNAP(Quilt *data
		, Quilt *containedData
		, ChunkEtherNet *parent
		, const unsigned short length
		, const unsigned int oui
		, const unsigned short pid)
	: Chunk(data, containedData, parent)
	, PayloadLength(length)
	, OUI(oui)
	, PID(pid)
{
}
