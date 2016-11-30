// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "ParserSessionTCP.h"

SessionID::SessionID(const std::shared_ptr<ChunkTCP> &chunk)
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

	uint64_t b1 = static_cast<uint64_t>(IP1.back()) << (8*2*3);
	uint64_t b2 = static_cast<uint64_t>(IP1.back()) << (8*2*2+1);
	uint64_t b3 = static_cast<uint64_t>(IP2.back()) << (8*2*2);
	uint64_t b4 = static_cast<uint64_t>(IP2.back()) << (8*2*1+1);
	uint64_t s3 = static_cast<uint64_t>(Port1) << (8*2*1);
	uint64_t s4 = Port2;

	Hash = b1 | b2 | b3 | b4 | s3 | s4;
}

std::shared_ptr<SessionTCP> ParserSessionTCP::Process(const std::shared_ptr<ChunkTCP> &parent)
{
	SessionID key(parent);
	auto it = SessionsCollector.find(key);
	if (it != SessionsCollector.end()) {
		SessionTCP *session = it->second.get();
		session->AddChunk(parent, IDGenerator.Next(), IsFuzzy);
		if ((session->Server->Payload != nullptr && session->Server->Payload->CoveredSize)
			|| (session->Client->Payload != nullptr && session->Client->Payload->CoveredSize)) {
			if (session->Follower != nullptr) {
				session->Follower->Recursive(it->second);
				AfterProcess(it->second);
				return (std::shared_ptr<SessionTCP>(nullptr));
			}
			return (it->second);
		} else {
			return (std::shared_ptr<SessionTCP>(nullptr));
		}
	} else {
		std::shared_ptr<SessionTCP> sessionTCP = std::make_shared<SessionTCP>(parent->BaseData, parent, IDGenerator.Next(), IsFuzzy);
		SessionsCollector.insert(std::make_pair(key, sessionTCP));
		AfterProcess(sessionTCP);
		return (std::shared_ptr<SessionTCP>(nullptr));
	}
}

void ParserSessionTCP::GarbageCollector()
{
	auto it = SessionsCollector.begin();
	while (it != SessionsCollector.end()) {
		unsigned long long diff = IDGenerator.Distance(it->second->LastInternalID);
		if (it->second->State == TCP_CLOSED) {
			if (diff > DeleteClosedAfter) {
				it = SessionsCollector.erase(it);
			} else {
				++it;
			}
		} else if (it->second->State == TCP_BYE1 || it->second->State == TCP_BYE2) {
			if (diff > DeleteClosingAfter) {
				it = SessionsCollector.erase(it);
			} else {
				++it;
			}
		} else {
			if (diff > DeleteInactiveAfter) {
				it = SessionsCollector.erase(it);
			} else {
				++it;
			}
		}
	}
}

void ParserSessionTCP::AfterProcess(const std::shared_ptr<SessionTCP> &session)
{
	if (session != nullptr) {
		// prevent access of followers to already processed data
		session->Client->ResetPayload();
		session->Server->ResetPayload();

		if (session->Inbox.size() > 4) { //-V112
			IsFuzzy = true;
		}

		if (IDGenerator.Get() % 1000 == 0) {
			GarbageCollector();
		}
	}
}

bool ParserSessionTCP::AfterRecursionHook(const std::shared_ptr<SessionTCP> &session, const std::exception *exn, bool found)
{
	if (session != nullptr)
		AfterProcess(session);

	return (found);
}

std::string ParserSessionTCP::ID()
{
	return (std::string("TCP_Session"));
}

std::string ParserSessionTCP::Description()
{
	return (std::string("TCP session"));
}
