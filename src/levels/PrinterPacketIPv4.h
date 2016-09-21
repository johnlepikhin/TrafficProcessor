
#ifndef SRC_LEVELS_PRINTERPACKETIPV4_H_
#define SRC_LEVELS_PRINTERPACKETIPV4_H_

#include "../types/Chunk.h"
#include "PacketIPv4.h"


class PrinterPacketIPv4: public Processor {
	/**
	 * Basic printer for PacketIPv4
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

#endif /* SRC_LEVELS_PRINTERPACKETIPV4_H_ */
