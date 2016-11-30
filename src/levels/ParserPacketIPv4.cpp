// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "ParserPacketIPv4.h"

inline uint64_t pair_of_IPv4(const std::shared_ptr<ChunkIPv4> &chunk)
{
	return ((static_cast<uint64_t>(chunk->SrcIP) << 32) | chunk->DstIP); //-V112
}

std::shared_ptr<PacketIPVariant> IPPairMap::AddChunk(const std::shared_ptr<ChunkIPv4> &chunk
		, uint64_t newLastInternalId)
{
	uint64_t pair = pair_of_IPv4(chunk);

	std::unordered_map<uint64_t, IPPacketMap>::iterator it = find(pair);

	if (it != end()) {
		(*it).second.LastInternalID = newLastInternalId;

		for (auto p_it = (*it).second.rbegin(); p_it != (*it).second.rend(); ++p_it) {
			if ((*p_it)->IPv4->Parent->ID == chunk->ID) {
				(*p_it)->IPv4->AddChunk(chunk);
				return (*p_it);
			}
		}

		PayloadQuilt payload = std::make_shared<CPayloadQuilt>();
		std::shared_ptr<PacketIPv4> pkt = std::make_shared<PacketIPv4>(chunk->BaseData, payload, chunk);
		std::shared_ptr<PacketIPVariant> v = std::make_shared<PacketIPVariant>(pkt, nullptr);
		(*it).second.push_back(v);

		return (v);
	} else {
		IPPacketMap IDMap;

		PayloadQuilt payload = std::make_shared<CPayloadQuilt>();
		std::shared_ptr<PacketIPv4> pkt = std::make_shared<PacketIPv4>(chunk->BaseData, payload, chunk);
		std::shared_ptr<PacketIPVariant> v = std::make_shared<PacketIPVariant>(pkt, nullptr);
		IDMap.push_back(v);
		IDMap.LastInternalID = newLastInternalId;

		emplace(pair, IDMap);

		return (v);
	}
}

void ParserPacketIPv4::GarbageCollector()
{
	auto it = IPCollector.begin();
	while (it != IPCollector.end()) {
		if (IDGenerator.Distance(it->second.LastInternalID) > DeleteInactiveAfter) {
			// TODO do not drop partially received IP packet but process it!
			// (modifications to RecursiveDelegator required
			it = IPCollector.erase(it);
		} else {
			++it;
		}
	}
}

bool ParserPacketIPv4::AfterRecursionHook(const std::shared_ptr<PacketIPVariant> &packet, const std::exception *exn, bool found)
{
	if (IDGenerator.Get() % 10000 == 0) {
		GarbageCollector();
	}

	PacketIPv4 *ipv4 = packet->IPv4.get();
	if (!ipv4->IsComplete)
		return (found);

	unsigned long long pair = pair_of_IPv4(ipv4->Parent);

	std::unordered_map<uint64_t, IPPacketMap>::iterator it = IPCollector.find(pair);

	if (it != IPCollector.end()) {
		for (auto p_it = (*it).second.rbegin(); p_it != (*it).second.rend(); ++p_it) {
			if ((*p_it)->IPv4->Parent->ID == packet->IPv4->Parent->ID) {
				(*it).second.erase((++p_it).base());
				break;
			}
		}

		// Leave empty IDMaps in IPCollector for future inserts with the same IP pairs.
		// Unused for a long time IDMaps will be erased by GarbageCollector.
//		if (IDMap->empty()) {
//			IPCollector.erase(it);
//		}
	}

	return (found);
}

std::shared_ptr<PacketIPVariant> ParserPacketIPv4::Process(const std::shared_ptr<ChunkIPv4> &parent)
{
	std::shared_ptr<PacketIPVariant> r = IPCollector.AddChunk(parent, IDGenerator.Next());
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
