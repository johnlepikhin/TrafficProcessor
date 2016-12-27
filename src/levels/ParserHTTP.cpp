// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "ParserHTTP.h"

#include "../core/utils.h"

bool ParserHTTP::CheckClientFlow(const std::shared_ptr<EndPoint> &flow) {
	try {
		if (flow->Payload.get() != nullptr && flow->Payload->CoveredSize) {
			std::string *preview = flow->GetPayloadPreview();
			return (ReqCheckRe.PartialMatch(*preview));
		}
	} catch (...) {
		return (false);
	}
	return (false);
}

bool ParserHTTP::CheckServerFlow(const std::shared_ptr<EndPoint> &flow) {
	try {
		if (flow->Payload.get() != nullptr && flow->Payload->CoveredSize) {
			std::string *preview = flow->GetPayloadPreview();
			return (RespCheckRe.PartialMatch(*preview));
		}
	} catch (...) {
		return (false);
	}
	return (false);
}

std::shared_ptr<ChunkHTTP> ParserHTTP::ParseClient(const std::shared_ptr<SessionTCP> &session
		, std::shared_ptr<ChunkHTTP> follower) {
	std::vector<std::pair<std::string, std::string> > headers;

	std::shared_ptr<ChunkHTTP> chunk = (follower != nullptr)
		? follower
		: std::make_shared<ChunkHTTP>(session->BaseData, session->Client->Payload, session, nullptr, nullptr);

	chunk->LastIsRequest = true;
	chunk->LastIsResponse = false;

	try {
		std::string payload = session->Client->Payload->GetMaxSubString(0, 20000);
		pcrecpp::StringPiece input(payload);
		std::string method, uri;
		ReqFirstLineRe.FindAndConsume(&input, &method, &uri);
		std::string key, value;
		std::string host("");
		while (HeaderLineRe.FindAndConsume(&input, &key, &value)) {
			if (util::iequals(key, "host"))
				host = value;
			headers.push_back(std::make_pair(key, value));
		}

		std::unique_ptr<HTTPRequest> request(new HTTPRequest(host
				, method
				, uri
				, headers));

		chunk->Request = std::move(request);

		return (chunk);
	} catch (...) {
		if (session->Follower != nullptr) {
			return (chunk);
		} else {
			return (std::shared_ptr<ChunkHTTP>(nullptr));
		}
	}
}

std::shared_ptr<ChunkHTTP> ParserHTTP::ParseServer(
		const std::shared_ptr<SessionTCP> &session
		, std::shared_ptr<ChunkHTTP> follower) {
	std::vector<std::pair<std::string, std::string> > headers;

	std::shared_ptr<ChunkHTTP> chunk = (follower != nullptr)
		? follower
		: std::make_shared<ChunkHTTP>(session->BaseData, session->Client->Payload, session, nullptr, nullptr);

	chunk->LastIsRequest = false;
	chunk->LastIsResponse = true;

	try {
		std::string payload = session->Server->Payload->GetMaxSubString(0, 20000);
		pcrecpp::StringPiece input(payload);
		int code = 0;
		std::string message;
		RespFirstLineRe.FindAndConsume(&input, &code, &message);
		std::string key, value;
		while (HeaderLineRe.FindAndConsume(&input, &key, &value)) {
			headers.push_back(std::make_pair(key, value));
		}

		std::unique_ptr<HTTPResponse> response(new HTTPResponse(code, message, headers));
		chunk->Response = std::move(response);

		return (chunk);
	} catch (...) {
		if (session->Follower != nullptr) {
			return (chunk);
		} else {
			return (std::shared_ptr<ChunkHTTP>(nullptr));
		}
	}
}

std::shared_ptr<ChunkHTTP> ParserHTTP::FollowerProcess(const std::shared_ptr<SessionTCP> &session, std::shared_ptr<ChunkHTTP> follower)
{
	if (CheckClientFlow(session->Client)) {
		return(ParseClient(session, follower));

	} else if (CheckServerFlow(session->Client)) {
		session->SwapFlows();
		return (ParseServer(session, follower));

	} else if (CheckClientFlow(session->Server)) {
		session->SwapFlows();
		return (ParseClient(session, follower));

	} else if (CheckServerFlow(session->Server)) {
		return (ParseServer(session, follower));
	}

	if (follower != nullptr)
		return (follower);

	return (std::shared_ptr<ChunkHTTP>(nullptr));
}

/**
 * Returns unique ID for this Parser
 * @return ID
 */
std::string ParserHTTP::ID()
{
	return ("HTTP");
}

/**
 * Returns description for this Parser
 * @return Description
 */
std::string ParserHTTP::Description()
{
	return ("Simple HTTP parser");
}

ParserHTTP::ParserHTTP()
	: TCPSessionFollowerHolder<ChunkHTTP>()
	, ReqCheckRe("^(GET|PUT|HEAD|POST|DELETE|TRACE|CONNECT) ", pcrecpp::RE_Options().set_caseless(true))
	, ReqFirstLineRe("^(GET|PUT|HEAD|POST|DELETE|TRACE|CONNECT) +([^ ]+) +HTTP/[01]\\.[019]\r?\n", pcrecpp::RE_Options().set_caseless(true))
	, RespCheckRe("^HTTP/[01]\\.[019] +\\d+ +\\S")
	, RespFirstLineRe("^HTTP/[01]\\.[019] +(\\d+) +([^\r\n]+)\r?\n")
	, HeaderLineRe("^([^:]+): +([^\r\n]*)\r?\n", pcrecpp::RE_Options().set_caseless(true))
{
}
