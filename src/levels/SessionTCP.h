
#ifndef SRC_LEVELS_SESSIONTCP_H_
#define SRC_LEVELS_SESSIONTCP_H_

#include <map>
#include <memory>
#include "ChunkTCP.h"
#include "ChunkIPTraits.h"
#include "../types/PhantomQuilt.h"

enum tcp_session_state {
	TCP_INITIAL,
	TCP_HELLO,
	TCP_ESTABLISHED,
	TCP_BYE,
	TCP_CLOSED
};

class Flow
{
public:
	Flow(std::shared_ptr<ChunkTCP> chunk);

	typedef unsigned long SeqT;
	typedef std::map<SeqT, std::shared_ptr<ChunkTCP> > InboxT;

	InboxT Inbox;
	PayloadQuilt Payload;
	std::shared_ptr<ChunkTCP> FirstChunk;
	unsigned long long PayloadBytes;
	unsigned long long RawIfaceBytes;
	unsigned long LastSeq;
};

class SessionTCP: public Chunk<ChunkTCP> {
private:
	void ProcessFlowInbox(std::shared_ptr<Flow> flow);
	void AddChunkToFlow(std::shared_ptr<Flow> flow, std::shared_ptr<ChunkTCP> chunk);
	inline void UpgradeState(tcp_session_state newState) {
		if (State < newState)
			State = newState;
	}
public:
	SessionTCP(BaseQuilt baseData
			, std::shared_ptr<ChunkTCP> parent
			, unsigned long long lastInternalID);

	void AddChunk(std::shared_ptr<ChunkTCP> chunk, unsigned long long newLastInternalID);

	// public because followers can also detect direction and swap flows
	void SwapFlows();


	void CutFlowToNextChunk(std::shared_ptr<Flow> flow);
	void CheckFlowTimeOut(std::shared_ptr<Flow> flow);

	inline bool HasServerPayload() const {
		return (ServerFlow != nullptr && ServerFlow->Payload != nullptr);
	}

	inline bool HasClientPayload() const {
		return (ClientFlow != nullptr && ClientFlow->Payload != nullptr);
	}

	tcp_session_state State;

	std::shared_ptr<Flow> ClientFlow;
	std::shared_ptr<Flow> ServerFlow;

	bool DirectionDetected;

	unsigned long long LastInternalID;
};

#endif /* SRC_LEVELS_SESSIONTCP_H_ */
