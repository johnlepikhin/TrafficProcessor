
#include "SessionTCP.h"
#include <string.h>

inline bool isSameSource(chunkptr &chunk1, chunkptr &chunk2) {
	if (chunk1->SourcePort == chunk2->SourcePort) {
		if (chunk1->Parent->BinaryOfSrcIP() == chunk2->Parent->BinaryOfSrcIP()) {
			return (true);
		} else {
			return (false);
		}
	} else {
		return (false);
	}
}

inline bool isSameSource(chunkptr &chunk, EndPoint endpoint) {
	if (endpoint.LastChunk != nullptr) {
		return (isSameSource(chunk, endpoint.LastChunk));
	} else {
		return (false);
	}
}

SessionTCP::SessionTCP(BaseQuilt baseData
		, std::shared_ptr<ChunkTCP> parent
		, unsigned long long lastInternalID)
	: Chunk(baseData, nullptr, parent)
	, State(TCP_INITIAL)
	, LastInternalID(lastInternalID)
{
	AddChunk(parent, lastInternalID);
}

EndPoint::EndPoint()
	: LastChunk(nullptr)
	, PayloadBytes(0)
	, RawIfaceBytes(0)
	, NextExpectedSEQ(0)
{
}

void EndPoint::ResetPayload()
{
	Payload = nullptr;
	PreviewCreated = false;
}

std::shared_ptr<std::string> EndPoint::GetPayloadPreview()
{
	if (Payload == nullptr) {
		return (std::shared_ptr<std::string>(nullptr));
	} else {
		if (!PreviewCreated) {
			PreviewCreated = true;
			PayloadPreview = std::shared_ptr<std::string>(Payload->GetMaxSubString(0, 20));
		}
		return (PayloadPreview);
	}
}

chunkptr SessionTCP::PopChunk(const std::function <bool (chunkptr &candidate)> &filter)
{
	for (auto it : Inbox) {
		if (filter(it.second)) {
			Inbox.erase(it.first);
			return (it.second);
		}
	}

	return (nullptr);
}

void SessionTCP::SwapFlows()
{
	EndPoint *tmp = Server;
	Server = Client;
	Client = tmp;

	DirectionDetected = true;
}

void SessionTCP::AssignEndPoints(chunkptr &chunk, EndPoint **correct, EndPoint **other)
{
	if ((*correct)->LastChunk != nullptr && !isSameSource((*correct)->LastChunk, chunk)) {
		SwapFlows();
	} else if ((*other)->LastChunk != nullptr && isSameSource((*other)->LastChunk, chunk)) {
		SwapFlows();
	}
}

void SessionTCP::FillEndPoint(chunkptr &chunk)
{
	if (C_EP.LastChunk == nullptr && S_EP.LastChunk == nullptr) {
		C_EP.LastChunk = chunk;
		C_EP.PayloadBytes += chunk->PayloadLength;
		C_EP.RawIfaceBytes += chunk->BaseData->Length;
	} else if (C_EP.LastChunk == nullptr) {
		if (isSameSource(S_EP.LastChunk, chunk)) {
			S_EP.PayloadBytes += chunk->PayloadLength;
			S_EP.RawIfaceBytes += chunk->BaseData->Length;
		} else {
			C_EP.LastChunk = chunk;
			C_EP.PayloadBytes += chunk->PayloadLength;
			C_EP.RawIfaceBytes += chunk->BaseData->Length;
		}
	} else if (S_EP.LastChunk == nullptr) {
		if (isSameSource(C_EP.LastChunk, chunk)) {
			C_EP.PayloadBytes += chunk->PayloadLength;
			C_EP.RawIfaceBytes += chunk->BaseData->Length;
		} else {
			S_EP.LastChunk = chunk;
			S_EP.PayloadBytes += chunk->PayloadLength;
			S_EP.RawIfaceBytes += chunk->BaseData->Length;
		}
	} else {
		if (isSameSource(C_EP.LastChunk, chunk)) {
			C_EP.PayloadBytes += chunk->PayloadLength;
			C_EP.RawIfaceBytes += chunk->BaseData->Length;
		} else {
			S_EP.PayloadBytes += chunk->PayloadLength;
			S_EP.RawIfaceBytes += chunk->BaseData->Length;
		}
	}
}

void SessionTCP::AppendPayload(chunkptr &chunk, EndPoint *endpoint)
{
	if (endpoint->Payload == nullptr) {
		PayloadQuilt p(new CPayloadQuilt());
		endpoint->Payload = p;
	}
	endpoint->Payload->SewWithHole(chunk->Payload, endpoint->Payload->Length, chunk->PayloadLength);
}

void SessionTCP::AddChunk(std::shared_ptr<ChunkTCP> chunk, unsigned long long newLastInternalID)
{
	LastInternalID = newLastInternalID;
	FillEndPoint(chunk);
	Inbox.insert(std::make_pair(chunk->SeqNumber, chunk));

	while (1) {
		chunkptr c;
		int processed = 0;
		bool fin = false;
		switch (State) {
			case TCP_INITIAL:
				c = PopChunk(
						[](chunkptr chunk) { return (chunk->FlagSYN && !chunk->FlagACK); });
				if (c != nullptr) {
					State = TCP_HELLO1;
					AssignEndPoints(chunk, &Client, &Server);
					processed++;
				}
				break;

			case TCP_HELLO1:
				c = PopChunk(
						[](chunkptr chunk) { return (chunk->FlagSYN && chunk->FlagACK); });
				if (c != nullptr) {
					State = TCP_HELLO2;
					AssignEndPoints(chunk, &Server, &Client);
					Client->NextExpectedSEQ = chunk->ConfirmNumber;
					processed++;
				}
				break;

			case TCP_HELLO2:
				c = PopChunk(
						[this](chunkptr chunk) { return (chunk->FlagACK && chunk->SeqNumber == this->Client->NextExpectedSEQ); });
				if (c != nullptr) {
					State = TCP_ESTABLISHED;
					Server->NextExpectedSEQ = chunk->ConfirmNumber;
					processed++;
				}
				break;

			case TCP_ESTABLISHED:
			case TCP_BYE1:
				c = PopChunk(
						[this](chunkptr chunk) {return (chunk->FlagACK && chunk->SeqNumber == this->Client->NextExpectedSEQ); });

				if (c != nullptr) {
					Server->NextExpectedSEQ = chunk->ConfirmNumber;
					if (c->FlagFIN)
						fin=true;
					AppendPayload(c, Client);
					processed++;
				}

				c = PopChunk(
						[this](chunkptr chunk) { return (chunk->FlagACK && chunk->SeqNumber == this->Server->NextExpectedSEQ); });
				if (c != nullptr) {
					Client->NextExpectedSEQ = chunk->ConfirmNumber;
					if (c->FlagFIN)
						fin=true;
					AppendPayload(c, Server);
					processed++;
				}

				if (fin) {
					if (State == TCP_ESTABLISHED) {
						State = TCP_BYE1;
					} else {
						State = TCP_BYE2;
					}
				}
				break;

			case TCP_BYE2:
				c = PopChunk(
						[this](chunkptr chunk) {
					return (chunk->FlagACK
							&&
							( chunk->SeqNumber == this->Client->NextExpectedSEQ
							|| chunk->SeqNumber == this->Server->NextExpectedSEQ)); });

				if (c != nullptr) {
					State = TCP_CLOSED;
					processed++;
				}
				break;


			default:
				break;
		}
		if (!processed)
			return;
	}
}
