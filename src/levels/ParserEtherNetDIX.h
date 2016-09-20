/*
 * ParseEtherNetDIX.h
 *
 *  Created on: 16 авг. 2016 г.
 *      Author: eugene
 */

#ifndef SRC_LEVELS_PARSERETHERNETDIX_H_
#define SRC_LEVELS_PARSERETHERNETDIX_H_

#include "ChunkEtherNetDIX.h"

/**
 * Parser of DIX EtherNet frame
 */
class ParserEtherNetDIX: public Processor {
public:
	/**
	 * Try to get EtherNet DIX frame from data.
	 * @param data Reference to Data from where chunk was read
	 * @param parent Optional reference to parent Chunk
	 * @return NULL or parsed chunk
	 */
	ChunkEtherNetDIX *Process(Quilt *data, Chunk *parent);

	/**
	 * Returns unique ID for this Parser
	 * @return ID
	 */
	std::string ID();

	/**
	 * Returns description for this Parser
	 * @return Description
	 */
	std::string Description();
};

#endif /* SRC_LEVELS_PARSERETHERNETDIX_H_ */
