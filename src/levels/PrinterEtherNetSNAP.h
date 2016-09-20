
#ifndef SRC_LEVELS_PRINTERETHERNETSNAP_H_
#define SRC_LEVELS_PRINTERETHERNETSNAP_H_

#include "ChunkEtherNetSNAP.h"
#include "../types/Chunk.h"
#include <string>


class PrinterEtherNetSNAP: public Processor {
public:
	PrinterEtherNetSNAP();

	/**
	 * Basic printer for ChunkEtherNetSNAP
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

#endif /* SRC_LEVELS_PRINTERETHERNETSNAP_H_ */
