
#ifndef SRC_LEVELS_PARSERHTTPREQUESTREQUEST_H_
#define SRC_LEVELS_PARSERHTTPREQUESTREQUEST_H_

#include "../types/Processor.h"
#include "../types/Chunk.h"
#include <pcrecpp.h>

#include "HTTPRequest.h"

/**
 * Simple parser for HTTP requests
 */
class ParserHTTPRequest: public Processor<SessionTCP, HTTPRequest> {
private:
	pcrecpp::RE ReqCheckRe;
	pcrecpp::RE ReqFirstLineRe;
	pcrecpp::RE HeaderLineRe;
	bool CheckFlow(std::shared_ptr<EndPoint> flow);
	std::shared_ptr<HTTPRequest> ParseHTTP(std::shared_ptr<SessionTCP> session);
public:
	ParserHTTPRequest();

	/**
	 * Read HTTP request from data.
	 * @param session Reference to TCP session
	 * @return NULL or parsed chunk
	 */
	std::shared_ptr<HTTPRequest> Process(std::shared_ptr<SessionTCP> session);

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

#endif /* SRC_LEVELS_PARSERHTTPREQUESTREQUEST_H_ */
