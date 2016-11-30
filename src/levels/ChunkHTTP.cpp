// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "ChunkHTTP.h"

HTTPRequest::HTTPRequest(const std::string &host
			, const std::string &method
			, const std::string &uri
			, const std::vector<std::pair<std::string, std::string> > &headers)
	: Host(host)
	, Method(method)
	, URI(uri)
	, Headers(headers)
{
}

HTTPResponse::HTTPResponse(int code
			, const std::string &message
			, const std::vector<std::pair<std::string, std::string> > &headers)
	: Code(code)
	, Message(message)
	, Headers(headers)
{
}

ChunkHTTP::ChunkHTTP(const BaseQuilt &baseData
		, const PayloadQuilt &payload
		, const std::shared_ptr<SessionTCP> &parent
		, std::unique_ptr<HTTPRequest> request
		, std::unique_ptr<HTTPResponse> response)
	: Chunk<SessionTCP>(parent->BaseData, parent->Client->Payload, parent)
	, Request(std::move(request))
	, Response(std::move(response))
{
}
