
#ifndef SRC_LEVELS_PRINTERTCP_H_
#define SRC_LEVELS_PRINTERTCP_H_

#include "ChunkTCP.h"

class PrinterTCP: public Processor {
	/**
	 * Basic printer for TCP
	 * @param data Reference to Data from where chunk was read
	 * @param parent Optional reference to parent Chunk
	 * @return NULL
	 */
	Chunk *Process(Quilt *data, Chunk *parent);

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
