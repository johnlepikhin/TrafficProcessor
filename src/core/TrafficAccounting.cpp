
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <pcap/pcap.h>
#include <memory>
#include <unistd.h>

#include "utils.h"
#include <sparsed-ropes/Quilt.h>
#include "ProcessorsCollection.h"
#include "../levels/ParserEtherNet.h"
#include "../levels/ParserEtherNetDIX.h"
#include "../levels/ParserEtherNetRAW.h"
#include "../levels/ParserEtherNetSNAP.h"
#include "../levels/ParserEtherNet802LLC.h"
#include "../levels/ParserIPv4.h"
#include "../levels/PrinterIPv4.h"
#include "../levels/PrinterPacketIPv4.h"
#include "../levels/ParserPacketIPv4.h"
#include "../levels/PrinterEtherNetDIX.h"
#include "../levels/PrinterEtherNetRAW.h"
#include "../levels/PrinterEtherNetSNAP.h"
#include "../levels/PrinterEtherNet802LLC.h"

#include "../levels/ParserTCP.h"
#include "../levels/PrinterTCP.h"


using namespace std;

static ParserEtherNet *generateParseTree()
{
	PrinterTCP *printerTCP = new PrinterTCP();
	ParserTCP *parserTCP = new ParserTCP();
	parserTCP->AddFollower(ASFOLLOWER(ChunkTCP)printerTCP);

//	PrinterIPv4 *printerIPV4 = new PrinterIPv4();
	PrinterPacketIPv4 *printerPacketIPV4 = new PrinterPacketIPv4();

	ParserPacketIPv4 *parserPacketIPv4 = new ParserPacketIPv4();
	parserPacketIPv4->AddFollower(ASFOLLOWER(PacketIPv4)printerPacketIPV4);
	parserPacketIPv4->AddFollower(ASFOLLOWER(PacketIPv4)parserTCP);

	ParserIPv4 *parserIPv4 = new ParserIPv4();
//	parserIPv4->AddFollower(ASFOLLOWER(ChunkIPv4)printerIPV4);
	parserIPv4->AddFollower(ASFOLLOWER(ChunkIPv4)parserPacketIPv4);

	ParserEtherNetDIX *etherNetDIX = new ParserEtherNetDIX();
//	etherNetDIX->AddFollower(ASFOLLOWER(ChunkEtherNetDIX)new PrinterEtherNetDIX());
	etherNetDIX->AddFollower(ASFOLLOWER(ChunkEtherNetDIX)parserIPv4);
//	ethernetDIX->AddFollower(new ParserIPv6());

	ParserEtherNet *etherNet = new ParserEtherNet();
	etherNet->AddFollower(ASFOLLOWER(ChunkEtherNet)etherNetDIX);
//	etherNet->AddFollower(new ParserEtherNet802LLC());
//	etherNet->AddFollower(new ParserEtherNetRAW());
//	etherNet->AddFollower(new ParserEtherNetSNAP());

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
		ParserEtherNet *parser = generateParseTree();

		util::skipBytesInFD(FD, sizeof (pcap_file_header));

		BaseQuilt *InputData;
		while (!done) {
			try {
				InputData = util::quiltOfPcap(FD);
				parser->Recursive(InputData);
				delete InputData;
			} catch (...) {
				delete InputData;
				done = true;
			}
		}

		delete parser;
	}
};

static void registerParsers () {
	ProcessorsCollection *collection = ProcessorsCollection::getInstance();
	collection->Register((ProcessorTraits *)new ParserEtherNet());
	collection->Register((ProcessorTraits *)new ParserEtherNetDIX());
	collection->Register((ProcessorTraits *)new ParserEtherNetRAW());
	collection->Register((ProcessorTraits *)new ParserEtherNetSNAP());
	collection->Register((ProcessorTraits *)new ParserEtherNet802LLC());
	collection->Register((ProcessorTraits *)new ParserIPv4());
	collection->Register((ProcessorTraits *)new PrinterIPv4());
	collection->Register((ProcessorTraits *)new PrinterPacketIPv4());
	collection->Register((ProcessorTraits *)new ParserPacketIPv4());
	collection->Register((ProcessorTraits *)new PrinterEtherNetDIX());
	collection->Register((ProcessorTraits *)new PrinterEtherNetRAW());
	collection->Register((ProcessorTraits *)new PrinterEtherNetSNAP());
	collection->Register((ProcessorTraits *)new PrinterEtherNet802LLC());

	collection->Register((ProcessorTraits *)new PrinterTCP());
	collection->Register((ProcessorTraits *)new ParserTCP());
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
