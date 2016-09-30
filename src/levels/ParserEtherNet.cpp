
#include "ParserEtherNet.h"

std::string ParserEtherNet::ID()
{
	return (std::string("Ethernet"));
}

std::string ParserEtherNet::Description()
{
	return (std::string("Ethernet frame"));
}

std::shared_ptr<ChunkEtherNet> ParserEtherNet::Process(BaseQuilt data)
{
	unsigned long long DA = MAC::Make(data, 0);
	unsigned long long SA = MAC::Make(data, 6);

	unsigned short eType = data->GetShortBEOrFail(12);
	PayloadQuilt payload(new CPayloadQuilt(data, 14));

	std::shared_ptr<ChunkEtherNet> r(new ChunkEtherNet(data, payload, DA, SA, eType));

	return (r);
}
