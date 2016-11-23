
#include "ParserHTTP.h"

#include "../core/utils.h"

bool ParserHTTP::CheckClientFlow(std::shared_ptr<EndPoint> flow) {
	try {
		if (flow->Payload.get() != nullptr && flow->Payload->CoveredSize) {
			std::string *preview = flow->GetPayloadPreview().get();
			return (ReqCheckRe.PartialMatch(*preview));
		}
	} catch (...) {
	}
	return (false);
}

bool ParserHTTP::CheckServerFlow(std::shared_ptr<EndPoint> flow) {
	try {
		if (flow->Payload.get() != nullptr && flow->Payload->CoveredSize) {
			std::string *preview = flow->GetPayloadPreview().get();
			return (RespCheckRe.PartialMatch(*preview));
		}
	} catch (...) {
	}
	return (false);
}

std::shared_ptr<HTTP> ParserHTTP::ParseClient(std::shared_ptr<SessionTCP> session) {
	std::string *payload = session->Client->Payload->GetMaxSubString(0, 20000);
	try {
		pcrecpp::StringPiece input(*payload);
		std::string method, uri;
		ReqFirstLineRe.FindAndConsume(&input, &method, &uri);
		std::string key, value;
		std::string host("");
		std::vector<std::pair<std::string, std::string> > headers;
		while (HeaderLineRe.FindAndConsume(&input, &key, &value)) {
			if (util::iequals(key, "host"))
				host = value;
			headers.push_back(std::make_pair(key, value));
		}

		session->Follower = this->AsFollower();

		std::cout << "client: " << host << "\n";

		std::unique_ptr<HTTPRequest> request(new HTTPRequest(host
				, method
				, uri
				, headers));

		return (std::make_shared<HTTP>(session->BaseData, session->Client->Payload, session, std::move(request), nullptr));
	} catch (...) {
		delete payload;
		return (std::shared_ptr<HTTP>(nullptr));
	}
}

std::shared_ptr<HTTP> ParserHTTP::ParseServer(
		std::shared_ptr<SessionTCP> session) {
	std::string *payload = session->Server->Payload->GetMaxSubString(0, 20000);
	try {
		pcrecpp::StringPiece input(*payload);
		int code;
		std::string message;
		RespFirstLineRe.FindAndConsume(&input, &code, &message);
		std::string key, value;
		std::vector<std::pair<std::string, std::string> > headers;
		while (HeaderLineRe.FindAndConsume(&input, &key, &value)) {
			headers.push_back(std::make_pair(key, value));
		}

		session->Follower = this->AsFollower();

		std::cout << "server: " << code << " = " << message << "\n";

		std::unique_ptr<HTTPResponse> response(new HTTPResponse(code, message, headers));
		return (std::make_shared<HTTP>(session->BaseData, session->Server->Payload, session, nullptr, std::move(response)));
	} catch (...) {
		delete payload;
		return (std::shared_ptr<HTTP>(nullptr));
	}
}

std::shared_ptr<HTTP> ParserHTTP::Process(std::shared_ptr<SessionTCP> session)
{
	if (CheckClientFlow(session->Client)) {
		return(ParseClient(session));

	} else if (CheckServerFlow(session->Client)) {
		session->SwapFlows();
		return (ParseServer(session));

	} else if (CheckClientFlow(session->Server)) {
		session->SwapFlows();
		return (ParseClient(session));

	} else if (CheckServerFlow(session->Server)) {
		return (ParseServer(session));
	}
	return (std::shared_ptr<HTTP>(nullptr));
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
	: Processor<SessionTCP, HTTP>()
	, ReqCheckRe("^(GET|PUT|HEAD|POST|DELETE|TRACE|CONNECT) ", pcrecpp::RE_Options().set_caseless(true))
	, ReqFirstLineRe("^(GET|PUT|HEAD|POST|DELETE|TRACE|CONNECT) +([^ ]+) +HTTP/[01]\\.[019]\r?\n", pcrecpp::RE_Options().set_caseless(true))
	, RespCheckRe("^HTTP/[01]\\.[019] +\\d+ +\\S")
	, RespFirstLineRe("^HTTP/[01]\\.[019] +(\\d+) +([^\r\n]+)\r?\n")
	, HeaderLineRe("^([^:]+): +([^\r\n]*)\r?\n", pcrecpp::RE_Options().set_caseless(true))
{
}
