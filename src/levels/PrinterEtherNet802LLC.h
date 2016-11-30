
#ifndef SRC_LEVELS_PRINTERETHERNET802LLC_H_
#define SRC_LEVELS_PRINTERETHERNET802LLC_H_

#include "ChunkEtherNet802LLC.h"
#include "ChunkEtherNet.h"
#include "../types/Processor.h"

/**
 * Printer for Ethernet frames of type 802LLC
 */
class PrinterEtherNet802LLC: public Processor<ChunkEtherNet802LLC, ChunkRaw> {
public:
	PrinterEtherNet802LLC();

	/**
	 * Basic printer for ChunkEtherNet802LLC
	 * @param parent Optional reference to parent Chunk
	 * @return NULL
	 */
	std::shared_ptr<ChunkRaw> Process(const std::shared_ptr<ChunkEtherNet802LLC> &parent);

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
