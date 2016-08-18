#include <gtest/gtest.h>
#include <stdio.h>
#include <stdlib.h>
#include <sstream>
#include <string>
#include <iostream>
#include <iomanip>
#include "../../src/types/Data.h"
#include "../../src/types/IPv4Addr.h"

namespace testTypesIPv4 {

	unsigned int data_len = 4;

	unsigned char source[] = {
			// Data header
			0x60, 0xb3, 0xb1, 0x57, 0xa9, 0x6b, 0x03, 0x00, 0x04, 0x00, 0x00, 0x00, 0x04, 0x00, 0x00, 0x00,
			// Data
			0x01, 0x02, 0x03, 0x04 };

	unsigned int source_len = data_len + 16;

	unsigned char *resize(unsigned char newSize)
	{
		unsigned char *r = (unsigned char *)malloc(newSize+16);
		strncpy ((char *)&r[0], (char *)&source[0], newSize+16);
		r[8] = newSize;
		r[12] = newSize;
		return (r);
	}

	TEST(types_IPv4_constructor, HandlesSimpleParser) {
		std::stringstream input;
		input.write((char *)&source[0], source_len);
		Data data = Data(&input);

		IPv4Addr *addr = new IPv4Addr(&data, 0);

		EXPECT_FALSE(NULL == addr);
		delete addr;
	}

	TEST(types_IPv4_constructor, HandlesNULLData) {
		EXPECT_ANY_THROW(IPv4Addr(NULL, 0));
	}

	TEST(types_IPv4_constructor, HandlesEmptyData) {

		class LOCAL {
		public:
			static void handlesEmptyData() {
				std::stringstream input;
				unsigned char *empty_source = resize(0);
				input.write((char *)empty_source, 16);
				Data data = Data(&input);
				IPv4Addr(&data, 0);
				free (empty_source);
			}
		};

		EXPECT_THROW(LOCAL::handlesEmptyData(), std::underflow_error);
	}

	TEST(types_IPv4, HandlesHumanFormat) {
		std::stringstream input;
		input.write((char *)&source[0], source_len);
		Data data = Data(&input);

		IPv4Addr addr = IPv4Addr(&data, 0);

		EXPECT_STREQ("1.2.3.4", addr.asString().c_str());
	}

	TEST(types_IPv4, HandlesBinaryFormat) {
		std::stringstream input;
		input.write((char *)&source[0], source_len);
		Data data = Data(&input);

		IPv4Addr addr = IPv4Addr(&data, 0);

		EXPECT_STREQ("\x01\x02\x03\x04", addr.asBinary().c_str());
	}
};
