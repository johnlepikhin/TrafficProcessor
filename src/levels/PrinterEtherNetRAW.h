
#ifndef SRC_LEVELS_PRINTERETHERNETRAW_H_
#define SRC_LEVELS_PRINTERETHERNETRAW_H_

#include "ChunkEtherNetRAW.h"
#include "../types/Processor.h"

/**
 * Printer for ethernet frames of raw format
 */
class PrinterEtherNetRAW: public Processor<ChunkEtherNetRAW, ChunkRaw> {
public:
	/**
	 * Basic printer for ChunkEtherNetRAW
	 * @param parent Optional reference to parent Chunk
	 * @return NULL
	 */
	std::shared_ptr<ChunkRaw> Process(const std::shared_ptr<ChunkEtherNetRAW> &parent);

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
