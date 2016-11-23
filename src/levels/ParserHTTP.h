
#ifndef SRC_LEVELS_PARSERHTTP_H_
#define SRC_LEVELS_PARSERHTTP_H_

#include "../types/Processor.h"
#include "../types/Chunk.h"
#include "SessionTCP.h"
#include <pcrecpp.h>

#include "ChunkHTTP.h"

/**
 * Simple parser for HTTP
 */
class ParserHTTP: public Processor<SessionTCP, ChunkHTTP> {
private:
	pcrecpp::RE ReqCheckRe;
	pcrecpp::RE ReqFirstLineRe;
	pcrecpp::RE RespCheckRe;
	pcrecpp::RE RespFirstLineRe;
	pcrecpp::RE HeaderLineRe;
	bool CheckClientFlow(std::shared_ptr<EndPoint> flow);
	std::shared_ptr<ChunkHTTP> ParseClient(std::shared_ptr<SessionTCP> session);
	bool CheckServerFlow(std::shared_ptr<EndPoint> flow);
	std::shared_ptr<ChunkHTTP> ParseServer(std::shared_ptr<SessionTCP> session);
public:
	ParserHTTP();

	/**
	 * Read HTTP request from data.
	 * @param session Reference to TCP session
	 * @return NULL or parsed chunk
	 */
	std::shared_ptr<ChunkHTTP> Process(std::shared_ptr<SessionTCP> session);

	/**
	 * Returns unique ID for this Parser
	 * @return ID
	 */
	std::string ID();

	/**
	 * Returns description for this Parser
	 * @return Description
	 */
	std::string Description();
};

#endif /* SRC_LEVELS_PARSERHTTP_H_ */
