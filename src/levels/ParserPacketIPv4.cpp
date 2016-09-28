
#include "ParserPacketIPv4.h"

inline unsigned long long pair_of_IPv4(const ChunkIPv4 *chunk)
{
	return (((unsigned long long)chunk->SrcIP << 32) + chunk->DstIP);
}

PacketIPv4 *IPPairMap::AddChunk(ChunkIPv4 *chunk)
{
	unsigned long long pair = pair_of_IPv4(chunk);

	std::unordered_map<unsigned long long, IPPacketMap *>::const_iterator it = find(pair);

	if (it != end()) {
		IPPacketMap *IDMap = (*it).second;

		for (auto p_it = IDMap->rbegin(); p_it != IDMap->rend(); ++p_it) {
			ChunkIPv4 *ipv4_chunk = (ChunkIPv4 *)(*p_it)->Parent;
			if (ipv4_chunk->ID == chunk->ID) {
				(*p_it)->AddChunk(chunk);
				return (*p_it);
			}
		}

		PayloadQuilt *payload = new PayloadQuilt();
		PacketIPv4 *pkt = new PacketIPv4(chunk->BaseData, payload, chunk);
		IDMap->push_back(pkt);

		return (pkt);
	} else {
		IPPacketMap *IDMap = new IPPacketMap();

		PayloadQuilt *payload = new PayloadQuilt();
		PacketIPv4 *pkt = new PacketIPv4(chunk->BaseData, payload, chunk);
		IDMap->push_back(pkt);

		emplace(pair, IDMap);

		return (pkt);
	}
}

void ParserPacketIPv4::DestroyChunk(PacketIPv4 *packet)
{
	unsigned long long pair = pair_of_IPv4(packet->Parent);

	std::unordered_map<unsigned long long, IPPacketMap *>::const_iterator it = IPCollector.find(pair);

	if (it != IPCollector.end()) {
		IPPacketMap *IDMap = (*it).second;

		for (auto p_it = IDMap->rbegin(); p_it != IDMap->rend(); ++p_it) {
			ChunkIPv4 *ipv4_chunk = (ChunkIPv4 *)(*p_it)->Parent;
			if (ipv4_chunk->ID == packet->Parent->ID) {
				IDMap->erase((++p_it).base());
				break;
			}
		}

		// TODO: check+remove periodically
//		if (IDMap->empty()) {
//			delete IDMap;
//			IPCollector.erase(it);
//		}
	}

	if (packet->RefCounter)
		packet->DecrRefs(1);

	if (!packet->RefCounter) {
		delete packet;
	}
}

ParserPacketIPv4::~ParserPacketIPv4()
{
	for (auto pair_it = IPCollector.begin(); pair_it != IPCollector.end(); ++pair_it) {
		for (auto id_it = pair_it->second->begin(); id_it != pair_it->second->end(); ++id_it) {
			delete (*id_it);
		}
		delete pair_it->second;
	}
}

PacketIPv4 *ParserPacketIPv4::Process(ChunkIPv4 *parent)
{
	PacketIPv4 *r = IPCollector.AddChunk(parent);
	if (!r->IsComplete) {
		r->IncrRefs(1);
	}

	return (r);
}

std::string ParserPacketIPv4::ID()
{
	return (std::string("IPv4_Packet"));
}

std::string ParserPacketIPv4::Description()
{
	return (std::string("IPv4 packet"));
}
