// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <pcap/pcap.h>
#include <memory>
#include <unistd.h>

#include "utils.h"
#include "../../../cpp-quilt-strings/src/Quilt.h"
#include "ProcessorsCollection.h"
#include "../levels/ParserEtherNet.h"
#include "../levels/ParserEtherNetDIX.h"
#include "../levels/ParserEtherNetRAW.h"
#include "../levels/ParserEtherNetSNAP.h"
#include "../levels/ParserEtherNet802LLC.h"

#include "../levels/ParserIPv4.h"

#include "../levels/ParserIPv6.h"

#include "../levels/ParserPacketIPv4.h"

#include "../levels/ParserTCP.h"
#include "../levels/ParserSessionTCP.h"

#include "../levels/ParserUDP.h"

#include "../levels/ParserHTTP.h"
#include "../levels/ParserPacketMySQL.h"
#include "../levels/ParserChunkSSL.h"

using namespace std;

static ParserEtherNet generateParseTree()
{
	ParserHTTP *parserHTTP = new ParserHTTP();
//	ParserPacketMySQL *parserMySQL = new ParserPacketMySQL();
//	ParserChunkSSL *parserChunkSSL = new ParserChunkSSL();


//	ParserUDP *parserUDP = new ParserUDP();
//	PrinterUDP *printerUDP = new PrinterUDP();
//	parserUDP->AddFollower(printerUDP->AsFollower());

//	PrinterSessionTCP *printerSessionTCP = new PrinterSessionTCP();

	ParserSessionTCP *parserSessionTCP = new ParserSessionTCP();
	parserSessionTCP->AddFollower(parserHTTP->AsFollower());
//	parserSessionTCP->AddFollower(parserMySQL->AsFollower());
//	parserSessionTCP->AddFollower(parserChunkSSL->AsFollower());
//	parserSessionTCP->AddFollower(printerSessionTCP->AsFollower());

//	PrinterTCP *printerTCP = new PrinterTCP();
	ParserTCP *parserTCP = new ParserTCP();
//	parserTCP->AddFollower(printerTCP->AsFollower());
	parserTCP->AddFollower(parserSessionTCP->AsFollower());

//	PrinterIPv4 *printerIPV4 = new PrinterIPv4();
//	PrinterPacketIPv4 *printerPacketIPV4 = new PrinterPacketIPv4();
//
	ParserPacketIPv4 *parserPacketIPv4 = new ParserPacketIPv4();
//	parserPacketIPv4->AddFollower(printerPacketIPV4->AsFollower());
	parserPacketIPv4->AddFollower(parserTCP->AsFollower());
//	parserPacketIPv4->AddFollower(parserUDP->AsFollower());

//	PrinterIPv6 *printerIPV6 = new PrinterIPv6();

//	ParserIPv6 *parserIPv6 = new ParserIPv6();
//	parserIPv6->AddFollower(printerIPV6->AsFollower());

	ParserIPv4 *parserIPv4 = new ParserIPv4();
//	parserIPv4->AddFollower(printerIPV4->AsFollower());
	parserIPv4->AddFollower(parserPacketIPv4->AsFollower());

//	LeafProcessor<ChunkEtherNetDIX> *leafEtherNetDIX = new LeafProcessor<ChunkEtherNetDIX>();
	ParserEtherNetDIX *etherNetDIX = new ParserEtherNetDIX();
	ParserEtherNet802LLC *etherNet802LLC = new ParserEtherNet802LLC();
	ParserEtherNetRAW *etherNetRAW = new ParserEtherNetRAW();
	ParserEtherNetSNAP *etherNetSNAP = new ParserEtherNetSNAP();
//	etherNetDIX->AddFollower(leafEtherNetDIX->AsFollower());
//	etherNetDIX->AddFollower((new PrinterEtherNetDIX())->AsFollower());

	etherNetDIX->AddFollower(reinterpret_cast<Processor<ChunkEtherNetDIX, void> *>(parserIPv4));
	etherNet802LLC->AddFollower(reinterpret_cast<Processor<ChunkEtherNet802LLC, void> *>(parserIPv4));
	etherNetRAW->AddFollower(reinterpret_cast<Processor<ChunkEtherNetRAW, void> *>(parserIPv4));
	etherNetSNAP->AddFollower(reinterpret_cast<Processor<ChunkEtherNetSNAP, void> *>(parserIPv4));

//	etherNetDIX->AddFollower(parserIPv6->AsFollower());

	ParserEtherNet etherNet;

//	LeafProcessor<ChunkEtherNet> *leafEtherNet = new LeafProcessor<ChunkEtherNet>();
//	etherNet.AddFollower(leafEtherNet->AsFollower());
	etherNet.AddFollower(etherNetDIX->AsFollower());
	etherNet.AddFollower(etherNet802LLC->AsFollower());
	etherNet.AddFollower(etherNetRAW->AsFollower());
	etherNet.AddFollower(etherNetSNAP->AsFollower());

//	etherNet.AddFollower(new ParserEtherNet802LLC());
//	etherNet.AddFollower(new ParserEtherNetRAW());
//	etherNet.AddFollower(new ParserEtherNetSNAP());

	return (etherNet);
}

class Reader {
public:
	int FD;

	Reader(int fd)
		: FD(fd)
	{
	}

	~Reader()
	{
	}

	void ReadPackets ()
	{
		bool done = false;
		ParserEtherNet parser = generateParseTree();

		util::skipBytesInFD(FD, sizeof (pcap_file_header));

		while (!done) {
			try {
				auto InputData = util::quiltOfPcap(FD);
				parser.Recursive(InputData);
			} catch (...) {
				done = true;
			}
		}
	}
};

static void registerParsers () {
//	ProcessorsCollection *collection = ProcessorsCollection::getInstance();
//	collection->Register((ProcessorTraits *)new ParserEtherNet());
//	collection->Register((ProcessorTraits *)new ParserEtherNetDIX());
//	collection->Register((ProcessorTraits *)new ParserEtherNetRAW());
//	collection->Register((ProcessorTraits *)new ParserEtherNetSNAP());
//	collection->Register((ProcessorTraits *)new ParserEtherNet802LLC());
//	collection->Register((ProcessorTraits *)new ParserIPv4());
//	collection->Register((ProcessorTraits *)new PrinterIPv4());
//	collection->Register((ProcessorTraits *)new PrinterPacketIPv4());
//	collection->Register((ProcessorTraits *)new ParserPacketIPv4());
//	collection->Register((ProcessorTraits *)new PrinterEtherNetDIX());
//	collection->Register((ProcessorTraits *)new PrinterEtherNetRAW());
//	collection->Register((ProcessorTraits *)new PrinterEtherNetSNAP());
//	collection->Register((ProcessorTraits *)new PrinterEtherNet802LLC());
//
//	collection->Register((ProcessorTraits *)new PrinterTCP());
//	collection->Register((ProcessorTraits *)new ParserTCP());
}

static void releaseParsers () {
	auto collection = ProcessorsCollection::getInstance();
	auto v = collection->AsVector();
	for (auto i : v) {
		delete (i);
	}
	v.clear();
	delete collection;
}

static void printParsers () {
	std::cout << "List of registered parsers:\n";
	auto collection = ProcessorsCollection::getInstance();
	auto v = collection->AsVector();
	for (auto i : v) {
		std::cout << " - " << i->ID() << " - " << i->Description() << "\n";
	}
}

int main () {
	registerParsers();
	printParsers();

	Reader reader = Reader(STDIN_FILENO);
	reader.ReadPackets();
	releaseParsers();

	return (0);
}
