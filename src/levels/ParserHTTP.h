
#ifndef SRC_LEVELS_PARSERHTTP_H_
#define SRC_LEVELS_PARSERHTTP_H_

#include "TCPSessionFollowerHolder.h"
#include "../types/Chunk.h"
#include "SessionTCP.h"
#include <pcrecpp.h>

#include "ChunkHTTP.h"

/**
 * Simple parser for HTTP
 */
class ParserHTTP: public TCPSessionFollowerHolder<ChunkHTTP> {
private:
	pcrecpp::RE ReqCheckRe;
	pcrecpp::RE ReqFirstLineRe;
	pcrecpp::RE RespCheckRe;
	pcrecpp::RE RespFirstLineRe;
	pcrecpp::RE HeaderLineRe;
	bool CheckClientFlow(const std::shared_ptr<EndPoint> &flow);
	std::shared_ptr<ChunkHTTP> ParseClient(const std::shared_ptr<SessionTCP> &session
			, std::shared_ptr<ChunkHTTP> follower);
	bool CheckServerFlow(const std::shared_ptr<EndPoint> &flow);
	std::shared_ptr<ChunkHTTP> ParseServer(const std::shared_ptr<SessionTCP> &session
			, std::shared_ptr<ChunkHTTP> follower);
public:
	ParserHTTP();

	/**
	 * Read HTTP request from data.
	 * @param session Reference to TCP session
	 * @return NULL or parsed chunk
	 */
	std::shared_ptr<ChunkHTTP> FollowerProcess(const std::shared_ptr<SessionTCP> &session, std::shared_ptr<ChunkHTTP> follower);

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
