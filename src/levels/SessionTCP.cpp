// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "SessionTCP.h"
#include <string.h>

inline bool isSameSource(const chunkptr &chunk1, const chunkptr &chunk2) {
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

inline bool isSameSource(const chunkptr &chunk, const EndPoint &endpoint) {
	if (endpoint.LastChunk != nullptr) {
		return (isSameSource(chunk, endpoint.LastChunk));
	} else {
		return (false);
	}
}

SessionTCP::SessionTCP(const BaseQuilt &baseData
		, const std::shared_ptr<ChunkTCP> &parent
		, unsigned long long lastInternalID
		, bool isFuzzy)
	: Chunk(baseData, nullptr, parent)
	, State(TCP_INITIAL)
	, LastInternalID(lastInternalID)
{
	C_EP = std::make_shared<EndPoint>();
	S_EP = std::make_shared<EndPoint>();
	Server = S_EP;
	Client = C_EP;
	AddChunk(parent, lastInternalID, isFuzzy);
	Follower = nullptr;
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
	PayloadPreview = nullptr;
}

std::string *EndPoint::GetPayloadPreview()
{
	if (Payload == nullptr) {
		return (nullptr);
	} else {
		if (PayloadPreview == nullptr)
			PayloadPreview = std::unique_ptr<std::string>(new std::string(Payload->GetMaxSubString(0, 20)));
		return (PayloadPreview.get());
	}
}

chunkptr SessionTCP::PopChunk(const std::function <bool (chunkptr &candidate)> &filter, bool erase)
{
	for (auto it : Inbox) {
		if (filter(it.second)) {
			if (erase)
				Inbox.erase(it.first);
			return (it.second);
		}
	}

	return (nullptr);
}

void SessionTCP::SwapFlows()
{
	Server.swap(Client);

	DirectionDetected = true;
}

void SessionTCP::AssignEndPoints(const chunkptr &chunk, const std::shared_ptr<EndPoint> &correct, const std::shared_ptr<EndPoint> &other)
{
	if (correct->LastChunk != nullptr && !isSameSource(correct->LastChunk, chunk)) {
		SwapFlows();
	} else if (other->LastChunk != nullptr && isSameSource(other->LastChunk, chunk)) {
		SwapFlows();
	}
}

std::shared_ptr<EndPoint> SessionTCP::DetectEndPoint(const chunkptr &chunk)
{
	if (C_EP->LastChunk == nullptr && S_EP->LastChunk == nullptr) {
		return (C_EP);
	} else if (C_EP->LastChunk == nullptr) {
		if (isSameSource(S_EP->LastChunk, chunk)) {
			return (S_EP);
		} else {
			return (C_EP);
		}
	} else if (S_EP->LastChunk == nullptr) {
		if (isSameSource(C_EP->LastChunk, chunk)) {
			return (C_EP);
		} else {
			return (S_EP);
		}
	} else {
		if (isSameSource(C_EP->LastChunk, chunk)) {
			return (C_EP);
		} else {
			return (S_EP);
		}
	}
}

void SessionTCP::FillEndPoint(const chunkptr &chunk)
{
	if (C_EP->LastChunk == nullptr && S_EP->LastChunk == nullptr) {
		C_EP->LastChunk = chunk;
		C_EP->PayloadBytes += chunk->PayloadLength;
		C_EP->RawIfaceBytes += chunk->BaseData->Length;
	} else if (C_EP->LastChunk == nullptr) {
		if (isSameSource(S_EP->LastChunk, chunk)) {
			S_EP->PayloadBytes += chunk->PayloadLength;
			S_EP->RawIfaceBytes += chunk->BaseData->Length;
		} else {
			C_EP->LastChunk = chunk;
			C_EP->PayloadBytes += chunk->PayloadLength;
			C_EP->RawIfaceBytes += chunk->BaseData->Length;
		}
	} else if (S_EP->LastChunk == nullptr) {
		if (isSameSource(C_EP->LastChunk, chunk)) {
			C_EP->PayloadBytes += chunk->PayloadLength;
			C_EP->RawIfaceBytes += chunk->BaseData->Length;
		} else {
			S_EP->LastChunk = chunk;
			S_EP->PayloadBytes += chunk->PayloadLength;
			S_EP->RawIfaceBytes += chunk->BaseData->Length;
		}
	} else {
		if (isSameSource(C_EP->LastChunk, chunk)) {
			C_EP->PayloadBytes += chunk->PayloadLength;
			C_EP->RawIfaceBytes += chunk->BaseData->Length;
		} else {
			S_EP->PayloadBytes += chunk->PayloadLength;
			S_EP->RawIfaceBytes += chunk->BaseData->Length;
		}
	}
}

void SessionTCP::AppendPayload(const chunkptr &chunk, const std::shared_ptr<EndPoint> &endpoint)
{
	if (endpoint->Payload == nullptr) {
		PayloadQuilt p(new CPayloadQuilt());
		endpoint->Payload = p;
	}
	endpoint->Payload->SewWithHole(chunk->Payload, endpoint->Payload->Length, chunk->PayloadLength);
}

void SessionTCP::AddChunk(const std::shared_ptr<ChunkTCP> &chunk
		, unsigned long long newLastInternalID
		, bool isFuzzy)
{
	LastInternalID = newLastInternalID;
	FillEndPoint(chunk);

	if (isFuzzy) {
		std::shared_ptr<EndPoint> ep = DetectEndPoint(chunk);
		AppendPayload(chunk, ep);
		return;
	}

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
					AssignEndPoints(chunk, Client, Server);
					processed++;
				} else {
					if (Inbox.size() > 5) {
						c = PopChunk(
								[](chunkptr chunk) { return (!chunk->FlagSYN && !chunk->FlagFIN && chunk->FlagACK); }
							, false);
						if (c != nullptr) {
							State = TCP_ESTABLISHED;
							Client->NextExpectedSEQ = chunk->ConfirmNumber;
							Server->NextExpectedSEQ = chunk->SeqNumber;
						}
					}
				}
				break;

			case TCP_HELLO1:
				c = PopChunk(
						[](chunkptr chunk) { return (chunk->FlagSYN && chunk->FlagACK); });
				if (c != nullptr) {
					State = TCP_HELLO2;
					AssignEndPoints(chunk, Server, Client);
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
				} else {
					if (Inbox.size() > 5) {
						c = PopChunk(
								[](chunkptr chunk) { return (!chunk->FlagSYN && !chunk->FlagFIN && chunk->FlagACK); });
						if (c != nullptr) {
							Client->NextExpectedSEQ = chunk->ConfirmNumber;
							Server->NextExpectedSEQ = chunk->SeqNumber;
						}
					}
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
