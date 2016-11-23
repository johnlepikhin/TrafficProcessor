
#include "ChunkHTTP.h"

HTTPRequest::HTTPRequest(std::string host
			, std::string method
			, std::string uri
			, std::vector<std::pair<std::string, std::string> > headers)
	: Host(host)
	, Method(method)
	, URI(uri)
	, Headers(headers)
{
}

HTTPResponse::HTTPResponse(int code
			, std::string message
			, std::vector<std::pair<std::string, std::string> > headers)
	: Code(code)
	, Message(message)
	, Headers(headers)
{
}

ChunkHTTP::ChunkHTTP(BaseQuilt baseData
		, PayloadQuilt payload
		, std::shared_ptr<SessionTCP> parent
		, std::unique_ptr<HTTPRequest> request
		, std::unique_ptr<HTTPResponse> response)
	: Chunk<SessionTCP>(parent->BaseData, parent->Client->Payload, parent)
	, Request(std::move(request))
	, Response(std::move(response))
{
}
