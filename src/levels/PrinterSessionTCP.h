
#ifndef SRC_LEVELS_PRINTERSESSIONTCP_H_
#define SRC_LEVELS_PRINTERSESSIONTCP_H_

#include <memory>
#include "SessionTCP.h"
#include "ChunkRaw.h"
#include "../types/Processor.h"

/**
 * Printer for TCP sessions
 */
class PrinterSessionTCP: public Processor<SessionTCP, ChunkRaw> {
	/**
	 * Basic printer for TCP sessions
	 * @param parent Optional reference to TCP session. Payload in endpoints can be nullptr!
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
