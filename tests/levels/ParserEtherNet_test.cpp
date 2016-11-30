// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
/*
 * ParserEtherNet_test.cpp
 *
 *  Created on: 16 авг. 2016 г.
 *      Author: eugene
 */

#include <gtest/gtest.h>

#include "../../src/levels/ParserEtherNet.h"

namespace testParserEtherNet {
	//15:19:44.224169 28:28:5d:86:88:9a > 64:80:99:47:bc:ac, ethertype IPv4 (0x0800), length 112: 173.255.112.173.443 > 192.168.57.2.48334: Flags [P.], seq 1364983495:1364983541, ack 867086730, win 243, options [nop,nop,TS val 2867588903 ecr 176329713], length 46
	//        0x0000:  6480 9947 bcac 2828 5d86 889a 0800 4500  d..G..((].....E.
	//        0x0010:  0062 2e68 4000 2c06 07d7 adff 70ad c0a8  .b.h@.,.....p...
	//        0x0020:  3902 01bb bcce 515b fec7 33ae b18a 8018  9.....Q[..3.....
	//        0x0030:  00f3 56c8 0000 0101 080a aaeb ef27 0a82  ..V..........'..
	//        0x0040:  93f1 1703 0300 2950 d59f ac14 14d1 a940  ......)P.......@
	//        0x0050:  ce3a 6ff3 a26b d1a4 bda2 401f 332f 0612  .:o..k....@.3/..
	//        0x0060:  44f0 3a39 a72e b0e2 b883 4325 e2bb b80c  D.:9......C%....

	unsigned char packet[] = {
			0x60, 0xb3, 0xb1, 0x57, 0xa9, 0x6b, 0x03, 0x00, 0x70, 0x00, 0x00, 0x00,
			0x70, 0x00, 0x00, 0x00, 0x64, 0x80, 0x99, 0x47, 0xbc, 0xac, 0x28, 0x28,
			0x5d, 0x86, 0x88, 0x9a, 0x08, 0x00, 0x45, 0x00, 0x00, 0x62, 0x2e, 0x68,
			0x40, 0x00, 0x2c, 0x06, 0x07, 0xd7, 0xad, 0xff, 0x70, 0xad, 0xc0, 0xa8,
			0x39, 0x02, 0x01, 0xbb, 0xbc, 0xce, 0x51, 0x5b, 0xfe, 0xc7, 0x33, 0xae,
			0xb1, 0x8a, 0x80, 0x18, 0x00, 0xf3, 0x56, 0xc8, 0x00, 0x00, 0x01, 0x01,
			0x08, 0x0a, 0xaa, 0xeb, 0xef, 0x27, 0x0a, 0x82, 0x93, 0xf1, 0x17, 0x03,
			0x03, 0x00, 0x29, 0x50, 0xd5, 0x9f, 0xac, 0x14, 0x14, 0xd1, 0xa9, 0x40,
			0xce, 0x3a, 0x6f, 0xf3, 0xa2, 0x6b, 0xd1, 0xa4, 0xbd, 0xa2, 0x40, 0x1f,
			0x33, 0x2f, 0x06, 0x12, 0x44, 0xf0, 0x3a, 0x39, 0xa7, 0x2e, 0xb0, 0xe2,
			0xb8, 0x83, 0x43, 0x25, 0xe2, 0xbb, 0xb8, 0x0c
	};
	unsigned int packet_len = 128;


	TEST(levels_ParserEtherNet, HandlesProcessSimple) {
		struct Test {
			static void test () {
				std::stringstream input;
				input.write((char *)&packet[0], packet_len);
				Data data = Data(&input);
				ParserEtherNet parser;
				ChunkEtherNet *chunk = parser.Process(&data, NULL);
				delete chunk;
			}
		};

		EXPECT_NO_THROW(Test::test ());
	}

	TEST(levels_ParserEtherNet, HandlesUnderFlowData) {
		struct Test {
			static void test () {
				std::stringstream input;
				input.write((char *)&packet[0], 5);
				Data data = Data(&input);
				ParserEtherNet parser;
				ChunkEtherNet *chunk = parser.Process(&data, NULL);
				delete chunk;
			}
		};

		EXPECT_THROW(Test::test (), std::underflow_error);
	}


	TEST(levels_ParserEtherNet, HandlesProcessCheckContent) {
		std::stringstream input;
		input.write((char *)&packet[0], packet_len);
		Data data = Data(&input);
		ParserEtherNet parser;
		ChunkEtherNet *chunk = parser.Process(&data, NULL);
		EXPECT_STREQ("28:28:5d:86:88:9a", chunk->SourceMAC->asString().c_str());
		EXPECT_STREQ("64:80:99:47:bc:ac", chunk->DestinationMAC->asString().c_str());
		EXPECT_EQ(0x0800, chunk->EtherNetType);
		delete chunk;
	}
};
