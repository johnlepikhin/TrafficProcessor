
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <pcap/pcap.h>

#include "utils.h"
#include "../types/Data.h"
#include "ProcessorsCollection.h"
#include "../levels/ParserEtherNet.h"
#include "../levels/ParserEtherNetDIX.h"
#include "../levels/ParserEtherNetRAW.h"
#include "../levels/ParserEtherNetSNAP.h"
#include "../levels/ParserEtherNet802LLC.h"
#include "../levels/ParserIPv4.h"

using namespace std;

/**
 * @struct pkthdr
 * @brief Pcap binary packet header format
 */
//struct pkthdr {
//	const char data[8];			/**< data Magic number, version major/minor */
//    const bpf_u_int32 caplen;	/**< length of portion present */
//    const bpf_u_int32 len;		/**< length this packet (off wire) */
//};

static void packetsReader () {
	bool done = false;
	while (!done) {
		try {
			Data *p = new Data(&cin);
			delete p;
		} catch (...) {
			done = true;
		}
	}
}

void registerParsers () {
	ProcessorsCollection *collection = ProcessorsCollection::getInstance();
	collection->Register((Processor *)new ParserEtherNet());
	collection->Register((Processor *)new ParserEtherNetDIX());
	collection->Register((Processor *)new ParserEtherNetRAW());
	collection->Register((Processor *)new ParserEtherNetSNAP());
	collection->Register((Processor *)new ParserEtherNet802LLC());
	collection->Register((Processor *)new ParserIPv4());
}

void releaseParsers () {
	ProcessorsCollection *collection = ProcessorsCollection::getInstance();
	std::vector<Processor *> vector = collection->AsVector();
	for (std::vector<Processor *>::iterator i = vector.begin(); i != vector.end(); ++i) {
		vector.erase(i);
		delete (*i);
	}
	delete collection;
}

void printParsers () {
	std::cout << "List of registered parsers:\n";
	std::vector<Processor *> collection = ProcessorsCollection::getInstance()->AsVector();
	for (std::vector<Processor *>::iterator i = collection.begin(); i != collection.end(); ++i) {
		std::cout << (*i)->ID() << "\n";
	}
}

int main () {
	registerParsers();
	printParsers();

	pcap_file_header *hdr = (pcap_file_header *)util::mallocRead(&cin, sizeof (pcap_file_header));
	free (hdr);
	packetsReader();
	releaseParsers();
	return (0);
}
