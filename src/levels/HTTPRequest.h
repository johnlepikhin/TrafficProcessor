
#ifndef SRC_LEVELS_HTTPREQUEST_H_
#define SRC_LEVELS_HTTPREQUEST_H_

#include <unordered_map>
#include "../types/Chunk.h"
#include "SessionTCP.h"

class HTTPRequest: public Chunk<SessionTCP> {
public:
	/**
	 * Constructor for HTTP simple request
	 * @param parent Reference to TCP session
	 * @param payload Reference to TCP flow payload
	 * @param method HTTP method
	 * @param uri HTTP URI
	 */
	HTTPRequest(std::shared_ptr<SessionTCP> parent
			, std::string host
			, std::string method
			, std::string uri
			, std::unordered_map<std::string, std::string> headers);

	/**
	 * Host
	 */
	std::string Host;

	/**
	 * HTTP method
	 */
	std::string Method;

	/**
	 * HTTP URI
	 */
	std::string URI;

	/**
	 * HTTP headers
	 */
	std::unordered_map<std::string, std::string> Headers;
};

#endif
