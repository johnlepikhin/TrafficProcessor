
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

inline unsigned long prevSeq(unsigned long seq)
{
	if (seq == 0) {
		return (0xffffffff);
	} else {
		return (seq-1);
	}
}

inline bool isSameSource(const std::shared_ptr<Flow> flow, const std::shared_ptr<ChunkTCP> chunk)
{
	return (flow != nullptr
			&& flow->FirstChunk->SourcePort == chunk->SourcePort
			&& flow->FirstChunk->Parent->BinaryOfSrcIP().compare(chunk->Parent->BinaryOfSrcIP()));
}

Flow::Flow(std::shared_ptr<ChunkTCP> chunk)
	: FirstChunk(chunk)
	, PayloadBytes(0)
	, RawIfaceBytes(0)
	, LastSeq(prevSeq(chunk->SeqNumber))
{
}

void SessionTCP::ProcessFlowInbox(std::shared_ptr<Flow> flow)
{
	PayloadQuilt p(new CPayloadQuilt());
	flow->Payload = p;
	auto it = flow->Inbox.find(nextSeq(flow->LastSeq));
	unsigned long next;
	if (it != flow->Inbox.end()) {
		do {
			if (State != TCP_ESTABLISHED) {
				if ((*it).second->FlagSYN) {
					if ((*it).second->FlagACK) {
						UpgradeState(TCP_ESTABLISHED);
					} else {
						UpgradeState(TCP_HELLO);
					}
				}
			}

			// check every packet for the case of lost packets
			if ((*it).second->FlagFIN && (*it).second->FlagACK) {
				UpgradeState(TCP_BYE);
			} else {
				if (((*it).second->FlagACK && State == TCP_BYE)) {
					UpgradeState(TCP_CLOSED);
				}
			}

			if ((*it).second->FlagRST)
				UpgradeState(TCP_CLOSED);

			flow->Payload->SewWithHole((*it).second->Payload, flow->Payload->Length, (*it).second->PayloadLength);
			next = nextSeq((*it).second->SeqNumber);
			flow->LastSeq=(*it).second->SeqNumber;
			if (next) {
				it = flow->Inbox.erase(it);
			} else {
				flow->Inbox.erase(it);
				it = flow->Inbox.find(0);
			}
		} while (it != flow->Inbox.end() && (*it).second->SeqNumber == next);
	}
}

void SessionTCP::AddChunkToFlow(std::shared_ptr<Flow> flow, std::shared_ptr<ChunkTCP> chunk)
{
	// prevent access of followers to already processed data
	flow->Payload = nullptr;

	flow->RawIfaceBytes+=chunk->Parent->RawIfaceLength;
	flow->PayloadBytes+=chunk->PayloadLength;
	flow->Inbox.insert(std::make_pair(chunk->SeqNumber, chunk));

	if (nextSeq(flow->LastSeq) == chunk->SeqNumber)
		ProcessFlowInbox(flow);
}

void SessionTCP::SwapFlows()
{
	std::shared_ptr<Flow> tmp = ClientFlow;
	ClientFlow = ServerFlow;
	ServerFlow = tmp;
}

SessionTCP::SessionTCP(BaseQuilt baseData
		, std::shared_ptr<ChunkTCP> parent)
	: Chunk(baseData, nullptr, parent)
	, State(TCP_INITIAL)
	, ClientFlow(nullptr)
	, ServerFlow(nullptr)
	, DirectionDetected(false)
{
	AddChunk(parent);
}

void SessionTCP::AddChunk(std::shared_ptr<ChunkTCP> chunk)
{
	bool addedToServer = true;

	if (ServerFlow == nullptr && ClientFlow == nullptr) {
		ClientFlow = std::make_shared<Flow>(Flow(chunk));
		AddChunkToFlow(ClientFlow, chunk);
		addedToServer = false;
	} else if (ServerFlow == nullptr) {
		if (isSameSource(ClientFlow, chunk)) {
			AddChunkToFlow(ClientFlow, chunk);
			addedToServer = false;
		} else {
			ServerFlow = std::make_shared<Flow>(Flow(chunk));
			AddChunkToFlow(ServerFlow, chunk);
		}
	} else {
		if (isSameSource(ServerFlow, chunk)) {
			AddChunkToFlow(ServerFlow, chunk);
		} else {
			ClientFlow = std::make_shared<Flow>(Flow(chunk));
			AddChunkToFlow(ClientFlow, chunk);
			addedToServer = false;
		}
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
