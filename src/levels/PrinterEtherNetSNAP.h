
#ifndef SRC_LEVELS_PRINTERETHERNETSNAP_H_
#define SRC_LEVELS_PRINTERETHERNETSNAP_H_

#include "ChunkEtherNetSNAP.h"
#include "../types/Processor.h"

/**
 * Printer for ethernet frames of SNAP format
 */
class PrinterEtherNetSNAP: public Processor<ChunkEtherNetSNAP, ChunkRaw> {
public:
	/**
	 * Basic printer for ChunkEtherNetSNAP
	 * @param parent Optional reference to parent Chunk
	 * @return NULL
	 */
	std::shared_ptr<ChunkRaw> Process(std::shared_ptr<ChunkEtherNetSNAP> parent);

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

#endif /* SRC_LEVELS_PRINTERETHERNETSNAP_H_ */
