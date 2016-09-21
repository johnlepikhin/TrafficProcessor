
#include "ParserTCP.h"
#include "ChunkTCP.h"
#include "PacketIPv4.h"

std::string ParserTCP::ID()
{
	return (std::string("TCP_Fragment"));
}

std::string ParserTCP::Description()
{
	return (std::string("TCP fragment"));
}

ChunkTCP *ParserTCP::Process(Quilt *data, Chunk *p)
{
	PacketIPv4 *ip = dynamic_cast<PacketIPv4 *>(p);

	if (ip && 6 == ((ChunkIPv4 *)ip->Parent)->Protocol) {
		unsigned short pktLength = ip->ExpectedSize;

		unsigned int sourcePort = data->GetShortBEOrFail(0);
//		std::cout << "\n\n\source = " << sourcePort << "\n\n\n";

		unsigned short destinationPort = data->GetShortBEOrFail(2);

		unsigned short seqNumber(0);
		data->CopyBytesOrFail((char *)&seqNumber, 4, 4);

		unsigned short confirmNumber(0);
		data->CopyBytesOrFail((char *)&confirmNumber, 8, 4);

		unsigned short headerLength = (data->GetCharOrFail(12) >> 4) << 2;

		unsigned char flags = data->GetCharOrFail(14) >> 1;

		unsigned short windowSize = data->GetShortBEOrFail(15);

		QuiltCut *payload = new QuiltCut(data, headerLength);

		ChunkTCP *r = new ChunkTCP(data
				, payload
				, pktLength
				, headerLength
				, pktLength-headerLength
				, sourcePort
				, destinationPort
		);

		return (r);
	}

	return (0);
}
