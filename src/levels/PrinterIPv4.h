
#ifndef SRC_LEVELS_PRINTERIPV4_H_
#define SRC_LEVELS_PRINTERIPV4_H_

#include "ChunkIPv4.h"
#include "../types/Processor.h"

/**
 * Printer for IPv4 fragments
 */
class PrinterIPv4: public Processor<ChunkIPv4, ChunkRaw> {
public:
	/**
	 * Basic printer for ChunkIPv4
	 * @param parent Optional reference to parent Chunk
	 * @return NULL
	 */
	std::shared_ptr<ChunkRaw> Process(const std::shared_ptr<ChunkIPv4> &parent);

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

#endif /* SRC_LEVELS_PRINTERIPV4_H_ */
