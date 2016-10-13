/*
 * ChunkIPTraits.cpp
 *
 *  Created on: 27 сент. 2016 г.
 *      Author: eugene
 */

#include "ChunkIPTraits.h"

ChunkIPTraits::ChunkIPTraits(unsigned char protocol
		, std::shared_ptr<ChunkEtherNetDIX> iPEtherNetDIX)
	: Protocol(protocol)
	, IPEtherNetDIX(iPEtherNetDIX)
{
}
