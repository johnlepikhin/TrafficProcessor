
#ifndef SRC_LEVELS_PRINTERTCP_H_
#define SRC_LEVELS_PRINTERTCP_H_

#include "ChunkTCP.h"
#include "ChunkRaw.h"
#include "../types/Processor.h"

class PrinterTCP: public Processor<ChunkTCP, ChunkRaw> {
	/**
	 * Basic printer for TCP
	 * @param data Reference to Data from where chunk was read
	 * @param parent Optional reference to parent Chunk
	 * @return NULL
	 */
	ChunkRaw *Process(ChunkTCP *chunk);

	/**
	 * Returns unique ID for this Printer
	 * @return ID
	 */
	std::string ID();

	/**
	 * Returns description for this Printer
	 * @return Description
	 */
	std::string Description();
};

#endif /* SRC_LEVELS_PRINTERTCP_H_ */
