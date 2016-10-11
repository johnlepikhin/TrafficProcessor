
#ifndef SRC_LEVELS_SESSIONTCP_H_
#define SRC_LEVELS_SESSIONTCP_H_

#include <map>
#include <memory>
#include "ChunkTCP.h"
#include "ChunkIPTraits.h"
#include "../types/PhantomQuilt.h"

enum tcp_session_state {
	TCP_INITIAL,
	TCP_HELLO1,
	TCP_HELLO2,
	TCP_ESTABLISHED,
	TCP_BYE1,
	TCP_BYE2,
	TCP_CLOSED
};

typedef std::shared_ptr<ChunkTCP> chunkptr;

class EndPoint
{
private:
	std::shared_ptr<std::string> PayloadPreview;
	bool PreviewCreated = false;
public:
	EndPoint();
	void ResetPayload();
	std::shared_ptr<std::string> GetPayloadPreview();

	PayloadQuilt Payload;
	chunkptr LastChunk;
	unsigned long long PayloadBytes;
	unsigned long long RawIfaceBytes;
	unsigned long NextExpectedSEQ;
};

class SessionTCP: public Chunk<ChunkTCP> {
private:
	typedef unsigned long SeqT;
	typedef std::map<SeqT, std::shared_ptr<ChunkTCP> > InboxT;

	InboxT Inbox;

	chunkptr PopChunk(
			const std::function <bool (chunkptr &candidate)> &filter);

	void AssignEndPoints(chunkptr &chunk, EndPoint **correct, EndPoint **other);
	void FillEndPoint(chunkptr &chunk);
	void AppendPayload(chunkptr &chunk, EndPoint *endpoint);

	EndPoint C_EP;
	EndPoint S_EP;
public:
	SessionTCP(BaseQuilt baseData
			, chunkptr parent
			, unsigned long long lastInternalID);

	void AddChunk(chunkptr chunk, unsigned long long newLastInternalID);

	// public because followers can also detect direction and swap flows
	void SwapFlows();


//	void CutFlowToNextChunk(Flow flow);
//	void CheckFlowTimeOut(EndPoint &flow, EndPoint &otherFlow);

	tcp_session_state State = TCP_INITIAL;

	EndPoint *Client = &C_EP;
	EndPoint *Server = &S_EP;

	bool DirectionDetected = false;

	unsigned long long LastInternalID;
};

#endif /* SRC_LEVELS_SESSIONTCP_H_ */
