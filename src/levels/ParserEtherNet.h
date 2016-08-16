
#ifndef SRC_LEVELS_PARSERETHERNET_H_
#define SRC_LEVELS_PARSERETHERNET_H_

#include "ChunkEtherNet.h"

class ParserEtherNet : public Parser {
public:
	ChunkEtherNet *DoParse(Data *data, Chunk *parent);
	std::string ID();
	std::string Description();
};


#endif /* SRC_LEVELS_PARSERETHERNET_H_ */
