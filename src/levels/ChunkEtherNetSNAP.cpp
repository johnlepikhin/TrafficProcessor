
#include "ChunkEtherNetSNAP.h"

ChunkEtherNetSNAP::ChunkEtherNetSNAP(const Quilt *data
		, const Quilt *containedData
		, const ChunkEtherNet *parent
		, const unsigned short length
		, const unsigned int oui
		, const unsigned short pid)
	: Chunk(data, containedData, parent)
	, PayloadLength(length)
	, OUI(oui)
	, PID(pid)
{
}
