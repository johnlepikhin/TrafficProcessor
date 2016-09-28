
#ifndef SRC_LEVELS_PRINTERETHERNETRAW_H_
#define SRC_LEVELS_PRINTERETHERNETRAW_H_

#include "ChunkEtherNetRAW.h"
#include "../types/Processor.h"

class PrinterEtherNetRAW: public Processor<ChunkEtherNetRAW, ChunkRaw> {
public:
	PrinterEtherNetRAW();

	/**
	 * Basic printer for ChunkEtherNetRAW
	 * @param data Reference to Data from where chunk was read
	 * @param parent Optional reference to parent Chunk
	 * @return NULL
	 */
	ChunkRaw *Process(ChunkEtherNetRAW *parent);

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

#endif /* SRC_LEVELS_PRINTERETHERNETRAW_H_ */
