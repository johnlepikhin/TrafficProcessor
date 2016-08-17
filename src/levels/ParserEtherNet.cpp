/*
 * ParserEtherNet.cpp
 *
 *  Created on: 16 авг. 2016 г.
 *      Author: eugene
 */

#include "ParserEtherNet.h"

std::string ParserEtherNet::ID()
{
	return (std::string("Ethernet"));
}

std::string ParserEtherNet::Description()
{
	return (std::string("Ethernet frame"));
}

ChunkEtherNet *ParserEtherNet::DoParse(Data *data, Chunk *parent)
{
	MAC *DA = new MAC(data);
	MAC *SA = new MAC(data);
	try {
		const unsigned long dataPosition = data->Position;
		unsigned short eType = data->read2Reverse();
		ChunkEtherNet *r = new ChunkEtherNet(data, dataPosition, DA, SA, eType);
		return (r);
	} catch (...) {
		delete DA;
		delete SA;
		throw;
	}

//	if (eType > 1500) {
//		Data = new EtherFrame_DIX (this, DA, SA, eType, &score, size);
//	} else {
//		unsigned short b2;
//		anyReadAhead(&b2, 2, 0);
//		if (0xffff == b2) {
//			Data = new EtherFrame_RAW (this, DA, SA, eType, &score, size);
//		} else {
//			if (0xaaaa == b2) {
//				Data = new EtherFrame_SNAP (this, DA, SA, eType, &score, size);
//			} else {
//				Data = new EtherFrame802_3_LLC (this, DA, SA, eType, &score, size);
//			}
//		}
//	}
}
