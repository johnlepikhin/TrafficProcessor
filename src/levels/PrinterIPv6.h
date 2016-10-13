
#ifndef SRC_LEVELS_PRINTERIPV6_H_
#define SRC_LEVELS_PRINTERIPV6_H_

#include "ChunkIPv6.h"
#include "../types/Processor.h"

class PrinterIPv6: public Processor<ChunkIPv6, ChunkRaw> {
public:
	/**
	 * Basic printer for ChunkIPv6
	 * @param data Reference to Data from where chunk was read
	 * @param parent Optional reference to parent Chunk
	 * @return NULL
	 */
	std::shared_ptr<ChunkRaw> Process(std::shared_ptr<ChunkIPv6> parent);

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

#endif /* SRC_LEVELS_PRINTERIPV6_H_ */
