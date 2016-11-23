
#include "ParserHTTPRequestRequest.h"

bool ParserHTTPRequest::CheckFlow(std::shared_ptr<EndPoint> flow) {
	try {
		if (flow->Payload.get() != nullptr && flow->Payload->CoveredSize) {
			std::string *preview = flow->GetPayloadPreview().get();
			return (ReqCheckRe.PartialMatch(*preview));
		}
	} catch (...) {
	}
	return (false);
}

bool iequals(const string& a, const string& b)
{
    unsigned int sz = a.size();
    if (b.size() != sz)
        return (false);
    for (unsigned int i = 0; i < sz; ++i)
        if (tolower(a[i]) != tolower(b[i]))
            return (false);
    return (true);
}

std::shared_ptr<HTTPRequest> ParserHTTPRequest::ParseHTTP(
		std::shared_ptr<SessionTCP> session) {
	std::string *payload = session->Client->Payload->GetMaxSubString(0, 20000);
	try {
		pcrecpp::StringPiece input(*payload);
		std::string method, uri;
		ReqFirstLineRe.FindAndConsume(&input, &method, &uri);
		std::string key, value;
		std::string host("");
		std::unordered_map<std::string, std::string> headers;
		while (HeaderLineRe.FindAndConsume(&input, &key, &value)) {
			if (iequals(key, "host"))
				host = value;
			headers.emplace(key, value);
		}

		session->Follower = this->AsFollower();

		return (std::make_shared<HTTPRequest>(session
				, host
				, method
				, uri
				, headers));
	} catch (...) {
		delete payload;
		return (std::shared_ptr<HTTPRequest>(nullptr));
	}
}

std::shared_ptr<HTTPRequest> ParserHTTPRequest::Process(std::shared_ptr<SessionTCP> session)
{
	if (CheckFlow(session->Client)) {
		return (ParseHTTP(session));
	} else if (CheckFlow(session->Server)) {
		session->SwapFlows();
		return (ParseHTTP(session));
	}
	return (std::shared_ptr<HTTPRequest>(nullptr));
}

/**
 * Returns unique ID for this Parser
 * @return ID
 */
std::string ParserHTTPRequest::ID()
{
	return ("HTTPRequestSimple");
}

/**
 * Returns description for this Parser
 * @return Description
 */
std::string ParserHTTPRequest::Description()
{
	return ("Simple HTTP parser");
}

ParserHTTPRequest::ParserHTTPRequest()
	: Processor<SessionTCP, HTTPRequest>()
	, ReqCheckRe("^(GET|PUT|HEAD|POST|DELETE|TRACE|CONNECT) ", pcrecpp::RE_Options().set_caseless(true))
	, ReqFirstLineRe("^(GET|PUT|HEAD|POST|DELETE|TRACE|CONNECT) +([^ ]+) +HTTP/[01]\\.[019]\r?\n", pcrecpp::RE_Options().set_caseless(true))
	, HeaderLineRe("^([^:]+): +([^\r\n]*)\r?\n", pcrecpp::RE_Options().set_caseless(true))
{
}
