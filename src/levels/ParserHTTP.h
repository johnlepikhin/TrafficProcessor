
#ifndef SRC_LEVELS_PARSERHTTP_H_
#define SRC_LEVELS_PARSERHTTP_H_

#include "../types/Processor.h"
#include "../types/Chunk.h"
#include <pcrecpp.h>

#include "HTTP.h"

/**
 * Simple parser for HTTP
 */
class ParserHTTP: public Processor<SessionTCP, HTTP> {
private:
	pcrecpp::RE ReqCheckRe;
	pcrecpp::RE ReqFirstLineRe;
	pcrecpp::RE RespCheckRe;
	pcrecpp::RE RespFirstLineRe;
	pcrecpp::RE HeaderLineRe;
	bool CheckClientFlow(std::shared_ptr<EndPoint> flow);
	std::shared_ptr<HTTP> ParseClient(std::shared_ptr<SessionTCP> session);
	bool CheckServerFlow(std::shared_ptr<EndPoint> flow);
	std::shared_ptr<HTTP> ParseServer(std::shared_ptr<SessionTCP> session);
public:
	ParserHTTP();

	/**
	 * Read HTTP request from data.
	 * @param session Reference to TCP session
	 * @return NULL or parsed chunk
	 */
	std::shared_ptr<HTTP> Process(std::shared_ptr<SessionTCP> session);

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
