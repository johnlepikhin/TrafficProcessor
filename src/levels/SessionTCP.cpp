
#include "SessionTCP.h"
#include <string.h>

inline unsigned long nextSeq(unsigned long seq)
{
	if (seq == 0xffffffff) {
		return (0);
	} else {
		return (seq+1);
	}
}

inline bool isSameSource(const std::shared_ptr<Flow> &flow, const std::shared_ptr<ChunkTCP> chunk)
{
	return (flow != nullptr && chunk != nullptr && (*flow->FirstChunk)->SourcePort == chunk->SourcePort && (*flow->FirstChunk)->Parent->CompareSrcIP(chunk->Parent));
}

Flow::Flow(std::shared_ptr<ChunkTCP> chunk)
	: PayloadBytes(chunk->PayloadLength)
	, RawIfaceBytes(chunk->BaseData->Length)
	, LastSeq(chunk->SeqNumber)
{
}

void SessionTCP::ProcessFlowInbox(std::shared_ptr<Flow> flow)
{
	auto it = flow->Inbox.find(nextSeq(flow->LastSeq));
	unsigned long next;
	if (it != flow->Inbox.end()) {
		do {
			if (State != TCP_ESTABLISHED) {
				if ((*it).second->FlagACK) {
					UpgradeState(TCP_ESTABLISHED);
				} else if ((*it).second->FlagSYN) {
					UpgradeState(TCP_HELLO);
				}
			}
			// check every packet for the case of lost packets
			if ((*it).second->FlagFIN) {
				if ((*it).second->FlagACK) {
					UpgradeState(TCP_BYE);
				} else {
					UpgradeState(TCP_CLOSED);
				}
			}
			flow->Payload->SewWithHole((*it).second->Payload, Payload->Length, (*it).second->PayloadLength);
			flow->Inbox.erase(it);
			next = nextSeq((*it).second->SeqNumber);
			flow->LastSeq=(*it).second->SeqNumber;
			if (next) {
				it++;
			} else {
				it = flow->Inbox.find(0);
			}
		} while ((*it).second->SeqNumber == next);
	}
}

void SessionTCP::AddChunkToFlow(std::shared_ptr<Flow> flow, std::shared_ptr<ChunkTCP> chunk)
{
	// prevent access of followers to already processed data
	flow->Payload = nullptr;

	flow->RawIfaceBytes+=chunk->Parent->RawIfaceLength;
	flow->PayloadBytes+=chunk->PayloadLength;
	flow->Inbox[chunk->SeqNumber]=chunk;

	if (nextSeq(flow->LastSeq) == chunk->SeqNumber) {
		ProcessFlowInbox(flow);
	}
}

void SessionTCP::SwapFlows()
{
	std::shared_ptr<Flow> tmp = ClientFlow;
	ClientFlow = ServerFlow;
	ServerFlow = tmp;
}

SessionTCP::SessionTCP(BaseQuilt baseData
		, PayloadQuilt payload
		, std::shared_ptr<ChunkTCP> parent)
	: Chunk(baseData, payload, parent)
	, State(TCP_CLOSED)
	, ClientFlow(nullptr)
	, ServerFlow(nullptr)
	, DirectionDetected(false)
{
	AddChunk(parent);
}

void SessionTCP::AddChunk(std::shared_ptr<ChunkTCP> chunk)
{
	bool addedToServer = true;
	if (isSameSource(ServerFlow, chunk)) {
		AddChunkToFlow(ServerFlow, chunk);
	} else {
		addedToServer = false;
		if (ClientFlow == nullptr)
			ClientFlow = std::make_shared<Flow>(Flow(chunk));
		AddChunkToFlow(ClientFlow, chunk);
	}

	if (!DirectionDetected) {
		if (chunk->FlagSYN) {
			if (chunk->FlagACK) {
				// this is server's chunk
				if (!addedToServer)
					SwapFlows();
			} else {
				// this is client's chunk
				if (addedToServer)
					SwapFlows();
			}
		}
	}
}
