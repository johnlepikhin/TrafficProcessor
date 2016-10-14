
#ifndef SRC_LEVELS_PRINTERPACKETIPV4_H_
#define SRC_LEVELS_PRINTERPACKETIPV4_H_

#include "PacketIPv4.h"
#include "../types/Processor.h"

/**
 * Printer for defragmentated IPv4 packets
 */
class PrinterPacketIPv4: public Processor<PacketIPv4, ChunkRaw> {
	/**
	 * Basic printer for PacketIPv4
	 * @param data Reference to Data from where chunk was read
	 * @param parent Optional reference to parent Chunk
	 * @return NULL
	 */
	std::shared_ptr<ChunkRaw> Process(std::shared_ptr<PacketIPv4> parent);

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
