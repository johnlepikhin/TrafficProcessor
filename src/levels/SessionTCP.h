
#ifndef SRC_LEVELS_SESSIONTCP_H_
#define SRC_LEVELS_SESSIONTCP_H_

#include <map>
#include <memory>
#include "ChunkTCP.h"
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

/**
 * Representation of endpoint node
 */
class EndPoint
{
private:
	std::shared_ptr<std::string> PayloadPreview;
	bool PreviewCreated = false;
public:
	EndPoint();

	/**
	 * Reset payload. Useful when the data in the flow is processed and
	 * new fragments will be collected
	 */
	void ResetPayload();

	/**
	 * Get first 20 bytes of payload. This fragment is cached, so method is very fast.
	 * @return First 20 bytes of payload
	 */
	std::shared_ptr<std::string> GetPayloadPreview();

	/**
	 * Pointer to optional next data in the flow
	 */
	PayloadQuilt Payload;

	/**
	 * Last received TCP fragment
	 */
	chunkptr LastChunk;

	/**
	 * Amount of all received bytes in this TCP flow
	 */
	unsigned long long PayloadBytes;

	/**
	 * Amount of all received bytes in this TCP flow, including ethernet and IP headers
	 */
	unsigned long long RawIfaceBytes;

	/**
	 * Next expected sequence number
	 */
	unsigned long NextExpectedSEQ;
};

/**
 * Representation of TCP sessions
 */
class SessionTCP: public Chunk<ChunkTCP> {
private:
	typedef unsigned long SeqT;
	typedef std::map<SeqT, std::shared_ptr<ChunkTCP> > InboxT;

	InboxT Inbox;

	chunkptr PopChunk(
			const std::function <bool (chunkptr &candidate)> &filter);

	void AssignEndPoints(chunkptr &chunk, std::shared_ptr<EndPoint> correct, std::shared_ptr<EndPoint> other);
	void FillEndPoint(chunkptr &chunk);
	void AppendPayload(chunkptr &chunk, std::shared_ptr<EndPoint> endpoint);

	std::shared_ptr<EndPoint> C_EP, S_EP;
public:
	/**
	 * Constructor
	 * @param baseData Pointer to base data (well, useless in TCP sessions)
	 * @param parent Pointer to TCP fragment
	 * @param lastInternalID Unique ID of the last event related to this session (used for garbage collection)
	 */
	SessionTCP(BaseQuilt baseData
			, chunkptr parent
			, unsigned long long lastInternalID);

	/**
	 * Add TCP fragment to this session
	 * @param chunk TCP fragment
	 * @param newLastInternalID Unique ID of this event
	 */
	void AddChunk(chunkptr chunk, unsigned long long newLastInternalID);

	// public because followers can also detect direction and swap flows
	/**
	 * Swap Client and Server
	 */
	void SwapFlows();


//	void CutFlowToNextChunk(Flow flow);
//	void CheckFlowTimeOut(EndPoint &flow, EndPoint &otherFlow);

	/**
	 * Current state of the session
	 */
	tcp_session_state State = TCP_INITIAL;

	/**
	 * Reference to the Client endpoint (can be incorrect)
	 */
	std::shared_ptr<EndPoint> Client;

	/**
	 * Reference to the Server endpoint (can be incorrect)
	 */
	std::shared_ptr<EndPoint> Server;

	/**
	 * True if session direction is detected (Client and Server references are also become correct)
	 */
	bool DirectionDetected = false;

	/**
	 * Unique ID of the last event related to this session (used for garbage collection)
	 */
	unsigned long long LastInternalID;
};

#endif /* SRC_LEVELS_SESSIONTCP_H_ */
