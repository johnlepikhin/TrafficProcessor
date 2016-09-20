
#include "ParserPacketIPv4.h"

unsigned long long pair_of_IPv4(const ChunkIPv4 *chunk)
{
	return (((unsigned long long)chunk->SrcIP->asInt() << 32) + chunk->SrcIP->asInt());
}

PacketIPv4 *IPPairMap::AddChunk(ChunkIPv4 *chunk)
{
	unsigned long long pair = pair_of_IPv4(chunk);

	std::unordered_map<unsigned long long, IPPacketMap *>::const_iterator it = find(pair);

	if (it != end()) {
		IPPacketMap *IDMap = (*it).second;
		std::unordered_map<IPv4PacketID, PacketIPv4 *>::const_iterator id_it
			= IDMap->find(chunk->ID);

		if (id_it != IDMap->end()) {
			(*id_it).second->AddChunk(chunk);

			return ((*id_it).second);
		} else {
			PacketIPv4 *pkt = new PacketIPv4(chunk);
			IDMap->emplace(chunk->ID, pkt);

			return (pkt);
		}
	} else {
		IPPacketMap *IDMap = new IPPacketMap();
		emplace(pair, IDMap);

		PacketIPv4 *pkt = new PacketIPv4(chunk);
		IDMap->emplace(chunk->ID, pkt);

		return (pkt);
	}
}

void ParserPacketIPv4::DestroyChunk(Chunk *c)
{
	PacketIPv4 *packet = dynamic_cast<PacketIPv4 *>(c);

	const ChunkIPv4 *chunk = dynamic_cast<const ChunkIPv4 *>(packet->Parent);

	unsigned long long pair = pair_of_IPv4(chunk);

	std::unordered_map<unsigned long long, IPPacketMap *>::const_iterator it = IPCollector.find(pair);

	if (it != IPCollector.end()) {
		IPPacketMap *IDMap = (*it).second;
		std::unordered_map<IPv4PacketID, PacketIPv4 *>::const_iterator id_it
			= IDMap->find(chunk->ID);

		if (id_it != IDMap->end()) {
			IDMap->erase(id_it);
		}

		if (IDMap->empty()) {
			delete it->second;
			IPCollector.erase(it);
		}
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
			delete id_it->second;
		}
		delete pair_it->second;
	}
}

PacketIPv4 *ParserPacketIPv4::Process(Quilt *data, Chunk *p)
{
	ChunkIPv4 *parent = dynamic_cast<ChunkIPv4 *>(p);

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
