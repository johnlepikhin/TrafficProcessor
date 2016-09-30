
#include "ParserPacketIPv4.h"

inline unsigned long long pair_of_IPv4(const std::shared_ptr<ChunkIPv4> chunk)
{
	return (((unsigned long long)chunk->SrcIP << 32) + chunk->DstIP);
}

std::shared_ptr<PacketIPv4> IPPairMap::AddChunk(std::shared_ptr<ChunkIPv4> chunk)
{
	unsigned long long pair = pair_of_IPv4(chunk);

	std::unordered_map<unsigned long long, std::shared_ptr<IPPacketMap> >::const_iterator it = find(pair);

	if (it != end()) {
		std::shared_ptr<IPPacketMap> IDMap = (*it).second;

		for (auto p_it = IDMap->rbegin(); p_it != IDMap->rend(); ++p_it) {
			std::shared_ptr<ChunkIPv4> ipv4_chunk = (*p_it)->Parent;
			if (ipv4_chunk->ID == chunk->ID) {
				(*p_it)->AddChunk(chunk);
				return (*p_it);
			}
		}

		PayloadQuilt payload(new CPayloadQuilt());
		std::shared_ptr<PacketIPv4> pkt(new PacketIPv4(chunk->BaseData, payload, chunk));
		IDMap->push_back(pkt);

		return (pkt);
	} else {
		std::shared_ptr<IPPacketMap> IDMap(new IPPacketMap());

		PayloadQuilt payload(new CPayloadQuilt());
		std::shared_ptr<PacketIPv4> pkt(new PacketIPv4(chunk->BaseData, payload, chunk));
		IDMap->push_back(pkt);

		emplace(pair, IDMap);

		return (pkt);
	}
}

void ParserPacketIPv4::AfterRecursionHook(std::shared_ptr<PacketIPv4> packet, std::exception *exn, bool found)
{
	if (!packet->IsComplete)
		return;

	unsigned long long pair = pair_of_IPv4(packet->Parent);

	std::unordered_map<unsigned long long, std::shared_ptr<IPPacketMap> >::const_iterator it = IPCollector.find(pair);

	if (it != IPCollector.end()) {
		std::shared_ptr<IPPacketMap> IDMap = (*it).second;

		for (auto p_it = IDMap->rbegin(); p_it != IDMap->rend(); ++p_it) {
			std::shared_ptr<ChunkIPv4> ipv4_chunk = (*p_it)->Parent;
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
}

std::shared_ptr<PacketIPv4> ParserPacketIPv4::Process(std::shared_ptr<ChunkIPv4> parent)
{
	std::shared_ptr<PacketIPv4> r = IPCollector.AddChunk(parent);
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
