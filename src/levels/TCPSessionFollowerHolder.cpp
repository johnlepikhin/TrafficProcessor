// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "TCPSessionFollowerHolder.h"
#include "ChunkHTTP.h"
#include "PacketMySQL.h"

template <typename RESULT>
std::shared_ptr<RESULT> TCPSessionFollowerHolder<RESULT>::Process(const std::shared_ptr<SessionTCP> &session)
{
	auto it = SessionsMap.find(session->SessionID);
	if (it == SessionsMap.end()) {
		std::shared_ptr<RESULT> r = FollowerProcess(session, std::shared_ptr<RESULT>(nullptr));
		if (r != nullptr) {
			session->Follower = this->AsFollower();
			SessionsMap.emplace(session->SessionID, r);
			session->OnDestroyHooks.push_back([this](SessionTCP *session) {
				SessionsMap.erase(session->SessionID);
			});
		}
		return (r);
	}

	return (FollowerProcess(session, it->second));
}

template class TCPSessionFollowerHolder<ChunkHTTP>;
template class TCPSessionFollowerHolder<PacketMySQL>;
