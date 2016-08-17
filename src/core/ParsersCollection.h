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

class ParsersCollection {
private:
    std::vector<Processor *> collection;

    static ParsersCollection * p_instance;
    ParsersCollection() {};
	ParsersCollection( const ParsersCollection& ) {};
	ParsersCollection& operator= (const ParsersCollection &);
public:
	static ParsersCollection *getInstance() {
		if (!p_instance) {
			p_instance = new ParsersCollection();
		}
		return (p_instance);
	}
	void Register(Processor *parser) {
		collection.push_back(parser);
	}
	std::vector<Processor *> AsVector();
};

#endif /* SRC_CORE_PARSERSCOLLECTION_H_ */
