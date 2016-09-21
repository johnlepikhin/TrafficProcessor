
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
#include "../levels/ParserPacketIPv4.h"
#include "../levels/PrinterEtherNetDIX.h"
#include "../levels/PrinterEtherNetRAW.h"
#include "../levels/PrinterEtherNetSNAP.h"
#include "../levels/PrinterEtherNet802LLC.h"


using namespace std;

static ParserEtherNet *generateParseTree()
{
	PrinterIPv4 *printerIPV4 = new PrinterIPv4();

	ParserPacketIPv4 *parserPacketIPv4 = new ParserPacketIPv4();

	ParserIPv4 *parserIPv4 = new ParserIPv4();
	parserIPv4->AddFollower(printerIPV4);
	parserIPv4->AddFollower(parserPacketIPv4);

	ParserEtherNetDIX *etherNetDIX = new ParserEtherNetDIX();
	etherNetDIX->AddFollower(new PrinterEtherNetDIX());
	etherNetDIX->AddFollower(parserIPv4);
//	ethernetDIX->AddFollower(new ParserIPv6());

	ParserEtherNet *etherNet = new ParserEtherNet();
	etherNet->AddFollower(etherNetDIX);
	etherNet->AddFollower(new ParserEtherNet802LLC());
	etherNet->AddFollower(new ParserEtherNetRAW());
	etherNet->AddFollower(new ParserEtherNetSNAP());

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

		while (!done) {
			try {
				Quilt *InputData = util::quiltOfPcap(FD);
				parser->Recursive(InputData, 0);
				delete InputData;
			} catch (...) {
				done = true;
			}
		}

		delete parser;
	}
};

static void registerParsers () {
	ProcessorsCollection *collection = ProcessorsCollection::getInstance();
	collection->Register((Processor *)new ParserEtherNet());
	collection->Register((Processor *)new ParserEtherNetDIX());
	collection->Register((Processor *)new ParserEtherNetRAW());
	collection->Register((Processor *)new ParserEtherNetSNAP());
	collection->Register((Processor *)new ParserEtherNet802LLC());
	collection->Register((Processor *)new ParserIPv4());
	collection->Register((Processor *)new PrinterIPv4());
	collection->Register((Processor *)new ParserPacketIPv4());
	collection->Register((Processor *)new PrinterEtherNetDIX());
	collection->Register((Processor *)new PrinterEtherNetRAW());
	collection->Register((Processor *)new PrinterEtherNetSNAP());
	collection->Register((Processor *)new PrinterEtherNet802LLC());
}

static void releaseParsers () {
	ProcessorsCollection *collection = ProcessorsCollection::getInstance();
	std::vector<Processor *> vector = collection->AsVector();
	for (std::vector<Processor *>::iterator i = vector.begin(); i != vector.end(); ++i) {
		delete (*i);
	}
	vector.clear();
	delete collection;
}

static void printParsers () {
	std::cout << "List of registered parsers:\n";
	std::vector<Processor *> collection = ProcessorsCollection::getInstance()->AsVector();
	for (std::vector<Processor *>::iterator i = collection.begin(); i != collection.end(); ++i) {
		std::cout << " - " << (*i)->ID() << " - " << (*i)->Description() << "\n";
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
