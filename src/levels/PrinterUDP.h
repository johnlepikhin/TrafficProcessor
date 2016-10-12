
#ifndef SRC_LEVELS_PRINTERUDP_H_
#define SRC_LEVELS_PRINTERUDP_H_

#include "ChunkUDP.h"
#include "ChunkRaw.h"
#include "../types/Processor.h"

class PrinterUDP: public Processor<ChunkUDP, ChunkRaw> {
	/**
	 * Basic printer for UDP
	 * @param data Reference to Data from where chunk was read
	 * @param parent Optional reference to parent Chunk
	 * @return NULL
	 */
	std::shared_ptr<ChunkRaw> Process(std::shared_ptr<ChunkUDP> chunk);

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

#endif /* SRC_LEVELS_PRINTERUDP_H_ */
