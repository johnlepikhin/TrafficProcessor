
#ifndef SRC_LEVELS_PARSERTCP_H_
#define SRC_LEVELS_PARSERTCP_H_

#include "ChunkTCP.h"

class ParserTCP: public Processor {
	/**
	 * Try to get TCP from data.
	 * @param data Reference to Data from where chunk was read
	 * @param parent Optional reference to parent Chunk
	 * @return NULL or parsed chunk
	 */
	ChunkTCP *Process(Quilt *data, Chunk *parent);

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

#endif /* SRC_LEVELS_PARSERTCP_H_ */
