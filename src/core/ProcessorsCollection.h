/*
 * ParsersCollection.h
 *
 *  Created on: 16 авг. 2016 г.
 *      Author: eugene
 */

#ifndef SRC_CORE_PARSERSCOLLECTION_H_
#define SRC_CORE_PARSERSCOLLECTION_H_

#include <vector>
#include "../types/Chunk.h"

/**
 * Stores collection of
 */
class ProcessorsCollection {
private:
    std::vector<Processor *> collection;

    static ProcessorsCollection * p_instance;
    ProcessorsCollection() {};
	ProcessorsCollection( const ProcessorsCollection& ) {};
	ProcessorsCollection& operator= (const ProcessorsCollection &);
public:
	static ProcessorsCollection *getInstance() {
		if (!p_instance) {
			p_instance = new ProcessorsCollection();
		}
		return (p_instance);
	}
	void Register(Processor *parser) {
		collection.push_back(parser);
	}
	std::vector<Processor *> AsVector();
};

#endif /* SRC_CORE_PARSERSCOLLECTION_H_ */
