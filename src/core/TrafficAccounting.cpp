
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <pcap/pcap.h>

#include "../types/Data.h"
#include "utils.h"

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

int main () {
	pcap_file_header *hdr = (pcap_file_header *)util::mallocRead(&cin, sizeof (pcap_file_header));
	free (hdr);
	packetsReader();
	return (0);
}
