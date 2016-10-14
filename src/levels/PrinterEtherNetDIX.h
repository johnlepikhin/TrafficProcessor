
#ifndef SRC_LEVELS_PRINTERETHERNETDIX_H_
#define SRC_LEVELS_PRINTERETHERNETDIX_H_

#include "ChunkRaw.h"
#include "ChunkEtherNetDIX.h"
#include "../types/Chunk.h"
#include "../types/Processor.h"
#include <string>

/**
 * Printer for ethernet frames of type DIX
 */
class PrinterEtherNetDIX: public Processor<ChunkEtherNetDIX, ChunkRaw> {
public:
	/**
	 * Basic printer for ChunkEtherNetDIX
	 * @param dix Reference to DIX chunk
	 * @return NULL
	 */
	std::shared_ptr<ChunkRaw> Process(std::shared_ptr<ChunkEtherNetDIX> dix);

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

#endif /* SRC_LEVELS_PRINTERETHERNETDIX_H_ */
