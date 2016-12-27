
#ifndef SRC_LEVELS_CHUNKHTTP_H_
#define SRC_LEVELS_CHUNKHTTP_H_

#include <unordered_map>
#include "../types/Chunk.h"
#include "SessionTCP.h"

class HTTPRequest {
public:
	/**
	 * Constructor of HTTP requests
	 * @param host HTTP hostname
	 * @param method HTTP method
	 * @param uri HTTP URI
	 * @param headers HTTP headers list
	 */
	HTTPRequest(const std::string &host
			, const std::string &method
			, const std::string &uri
			, const std::vector<std::pair<std::string, std::string> > &headers);

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
	std::vector<std::pair<std::string, std::string> > Headers;
};

class HTTPResponse {
public:
	/**
	 * Constructor of HTTP requests
	 * @param host HTTP hostname
	 * @param method HTTP method
	 * @param uri HTTP URI
	 * @param headers HTTP headers list
	 */
	HTTPResponse(int code
			, const std::string &message
			, const std::vector<std::pair<std::string, std::string> > &headers);

	/**
	 * Code
	 */
	int Code;

	/**
	 * HTTP message
	 */
	std::string Message;

	/**
	 * HTTP headers
	 */
	std::vector<std::pair<std::string, std::string> > Headers;
};

class ChunkHTTP : public Chunk<SessionTCP> {
public:
	/**
	 * Constructor for HTTP chunks
	 * @param baseData Reference to base data (useless)
	 * @param payload Reference to payload
	 * @param parent Reference to TCP session
	 * @param request HTTP request
	 */
	ChunkHTTP(const BaseQuilt &baseData
		, const PayloadQuilt &payload
		, const std::shared_ptr<SessionTCP> &parent
		, std::unique_ptr<HTTPRequest> request
		, std::unique_ptr<HTTPResponse> response);

	/**
	 * Optional reference to HTTP request
	 */
	std::unique_ptr<HTTPRequest> Request;

	/**
	 * Optional reference to HTTP response
	 */
	std::unique_ptr<HTTPResponse> Response;

	/**
	 * Flags advise last received chunk status
	 */
	bool LastIsRequest = false;
	bool LastIsResponse = false;
};

#endif
