
#include "SessionTCP.h"
#include <string.h>

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

void SessionTCP::AssignEndPoints(chunkptr &chunk, EndPoint **correct, EndPoint **other)
{
	if ((*correct)->LastChunk == nullptr && (*other)->LastChunk == nullptr) {
		(*correct)->LastChunk = chunk;
	} else if ((*correct)->LastChunk != nullptr && (*correct)->LastChunk->SourcePort != chunk->SourcePort) {
		EndPoint **tmp = other;
		other = correct;
		correct = tmp;
	} else if ((*other)->LastChunk != nullptr && (*other)->LastChunk->SourcePort == chunk->SourcePort) {
		EndPoint **tmp = other;
		other = correct;
		correct = tmp;
	}

	DirectionDetected = true;
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
