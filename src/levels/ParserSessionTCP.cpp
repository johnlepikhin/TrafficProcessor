
#include "ParserSessionTCP.h"

SessionID::SessionID(std::shared_ptr<ChunkTCP> chunk)
{
	std::string ip1 = chunk->Parent->BinaryOfSrcIP();
	std::string ip2 = chunk->Parent->BinaryOfDstIP();
	int r1 = ip1.compare(ip2);
	if (r1 > 0) {
		IP1 = ip1;
		IP2 = ip2;
		Port1 = chunk->SourcePort;
		Port2 = chunk->DestinationPort;
	} else if (r1 < 0) {
		IP1 = ip2;
		IP2 = ip1;
		Port1 = chunk->DestinationPort;
		Port2 = chunk->SourcePort;
	} else {
		if (chunk->SourcePort >= chunk->DestinationPort) {
			IP1 = ip1;
			IP2 = ip2;
			Port1 = chunk->SourcePort;
			Port2 = chunk->DestinationPort;
		} else {
			IP1 = ip2;
			IP2 = ip1;
			Port1 = chunk->DestinationPort;
			Port2 = chunk->SourcePort;
		}
	}

	std::size_t b1 = (std::size_t)IP1.back() << (8*2*3);
	std::size_t b2 = (std::size_t)IP1.back() << (8*2*2+1);
	std::size_t b3 = (std::size_t)IP2.back() << (8*2*2);
	std::size_t b4 = (std::size_t)IP2.back() << (8*2*1+1);
	std::size_t s3 = (std::size_t)Port1 << (8*2*1);
	std::size_t s4 = Port2;

	Hash = b1 | b2 | b3 | b4 | s3 | s4;
}

std::shared_ptr<SessionTCP> ParserSessionTCP::Process(std::shared_ptr<ChunkTCP> parent)
{
	SessionID key(parent);
	auto it = SessionsCollector.find(key);
	if (it != SessionsCollector.end()) {
		it->second->AddChunk(parent);
		return (it->second);
	} else {
		std::shared_ptr<SessionTCP> sessionTCP(new SessionTCP(parent->BaseData, parent));
		SessionsCollector.insert(std::make_pair(key, sessionTCP));
		return (sessionTCP);
	}
}

void ParserSessionTCP::AfterRecursionHook(std::shared_ptr<SessionTCP> session, std::exception *exn, bool found)
{
	// TODO cleanup session only after a while
	if (session->State == TCP_CLOSED) {
		SessionID key(session->Parent);
		SessionsCollector.erase(key);
	}
}

std::string ParserSessionTCP::ID()
{
	return (std::string("TCP_Session"));
}

std::string ParserSessionTCP::Description()
{
	return (std::string("TCP session"));
}
