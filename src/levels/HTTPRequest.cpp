
#include "HTTPRequest.h"

HTTPRequest::HTTPRequest(std::shared_ptr<SessionTCP> parent
			, std::string host
			, std::string method
			, std::string uri
			, std::unordered_map<std::string, std::string> headers)
	: Chunk<SessionTCP>(parent->BaseData, parent->Client->Payload, parent)
	, Host(host)
	, Method(method)
	, URI(uri)
	, Headers(headers)
{
}
