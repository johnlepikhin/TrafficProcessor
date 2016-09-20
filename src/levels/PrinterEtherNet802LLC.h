
#ifndef SRC_LEVELS_PRINTERETHERNET802LLC_H_
#define SRC_LEVELS_PRINTERETHERNET802LLC_H_

#include "ChunkEtherNet802LLC.h"
#include "../types/Chunk.h"
#include <string>


class PrinterEtherNet802LLC: public Processor {
public:
	PrinterEtherNet802LLC();

	/**
	 * Basic printer for ChunkEtherNet802LLC
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

#endif /* SRC_LEVELS_PRINTERETHERNET802LLC_H_ */
