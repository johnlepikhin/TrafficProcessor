
#ifndef SRC_LEVELS_PRINTERIPV4_H_
#define SRC_LEVELS_PRINTERIPV4_H_

#include "ChunkIPv4.h"

class PrinterIPv4: public Processor {
public:
	/**
	 * Basic printer for ChunkIPv4
	 * @param data Reference to Data from where chunk was read
	 * @param parent Optional reference to parent Chunk
	 * @return NULL
	 */
	ChunkIPv4 *Process(Quilt *data, Chunk *parent);

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
