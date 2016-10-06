
#ifndef SRC_LEVELS_PRINTERSESSIONTCP_H_
#define SRC_LEVELS_PRINTERSESSIONTCP_H_

#include <memory>
#include "SessionTCP.h"
#include "ChunkRaw.h"
#include "../types/Processor.h"

class PrinterSessionTCP: public Processor<SessionTCP, ChunkRaw> {
	/**
	 * Basic printer for TCP sessions
	 * @param data Reference to Data from where chunk was read
	 * @param parent Optional reference to parent Chunk
	 * @return NULL
	 */
	std::shared_ptr<ChunkRaw> Process(std::shared_ptr<SessionTCP> session);

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

#endif /* SRC_LEVELS_PRINTERSESSIONTCP_H_ */
