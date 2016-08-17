/*
 * ParseEtherNetDIX.h
 *
 *  Created on: 16 авг. 2016 г.
 *      Author: eugene
 */

#ifndef SRC_LEVELS_PARSERETHERNETDIX_H_
#define SRC_LEVELS_PARSERETHERNETDIX_H_

#include "ChunkEtherNetDIX.h"

class ParserEtherNetDIX: public Processor {
public:
	ChunkEtherNetDIX *DoParse(Data *data, Chunk *parent);
	std::string ID();
	std::string Description();
};

#endif /* SRC_LEVELS_PARSERETHERNETDIX_H_ */
