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
    static ParsersCollection * p_instance;
    std::vector<Parser<void, void> > collection;
	ParsersCollection& operator= (const ParsersCollection &);
public:
	ParsersCollection() {};
	ParsersCollection( const ParsersCollection& ) {};
	static ParsersCollection *getInstance() {
		if (!p_instance) {
			p_instance = new ParsersCollection();
		}
		return (p_instance);
	}
	void Register(const Parser<void, void> parser) {
		collection.push_back(parser);
	}
};

#endif /* SRC_CORE_PARSERSCOLLECTION_H_ */
