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
 * Stores collection of Processors (singleton)
 */
class ProcessorsCollection {
private:
    std::vector<Processor *> collection;

    static ProcessorsCollection * p_instance;
    ProcessorsCollection() {};
	ProcessorsCollection( const ProcessorsCollection& ) {};
	ProcessorsCollection& operator= (const ProcessorsCollection &);
public:
	/**
	 * Returns instanse of singleton
	 * @return Reference to ProcessorsCollection object
	 */
	static ProcessorsCollection *getInstance() {
		if (!p_instance) {
			p_instance = new ProcessorsCollection();
		}
		return (p_instance);
	}

	/**
	 * Adds new Processor to the collection
	 * @param processor Processor to register
	 */
	void Register(Processor *processor) {
		collection.push_back(processor);
	}

	/**
	 * Returns the collection as std::vector
	 * @return Vector
	 */
	std::vector<Processor *> AsVector();
};

#endif /* SRC_CORE_PARSERSCOLLECTION_H_ */