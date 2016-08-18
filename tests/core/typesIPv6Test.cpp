#include <gtest/gtest.h>
#include <stdio.h>
#include <stdlib.h>
#include <sstream>
#include <string>
#include <iostream>
#include <iomanip>
#include "../../src/types/Data.h"
#include "../../src/types/IPv6Addr.h"

namespace testTypesIPv6 {

unsigned int data_len = 16;

	unsigned char source[] = {
			// Data header
			0x60, 0xb3, 0xb1, 0x57, 0xa9, 0x6b, 0x03, 0x00, 0x10, 0x00, 0x00, 0x00, 0x10, 0x00, 0x00, 0x00,
			// Data
			0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f, 0x10 };

	unsigned int source_len = data_len + 16;

	unsigned char *resize(unsigned char newSize)
	{
		unsigned char *r = (unsigned char *)malloc(newSize+16);
		strncpy ((char *)&r[0], (char *)&source[0], newSize+16);
		r[8] = newSize;
		r[12] = newSize;
		return (r);
	}

	TEST(types_IPv6_constructor, HandlesSimpleParser) {
		std::stringstream input;
		input.write((char *)&source[0], source_len);
		Data data = Data(&input);

		IPv6Addr *addr = new IPv6Addr(&data, 0);

		EXPECT_FALSE(NULL == addr);
		delete addr;
	}

	TEST(types_IPv6_constructor, HandlesNULLData) {
		EXPECT_ANY_THROW(IPv6Addr(NULL, 0));
	}

	TEST(types_IPv6_constructor, HandlesEmptyData) {

		class LOCAL {
		public:
			static void handlesEmptyData() {
				std::stringstream input;
				unsigned char *empty_source = resize(0);
				input.write((char *)empty_source, 16);
				Data data = Data(&input);
				IPv6Addr(&data, 0);
				free (empty_source);
			}
		};

		EXPECT_THROW(LOCAL::handlesEmptyData(), std::underflow_error);
	}

	TEST(types_IPv6, HandlesHumanFormat) {
		std::stringstream input;
		input.write((char *)&source[0], source_len);
		Data data = Data(&input);

		IPv6Addr addr = IPv6Addr(&data, 0);
		EXPECT_STREQ("01:02:03:04:05:06:07:08:09:0a:0b:0c:0d:0e:0f:10", addr.asString().c_str());
	}

	TEST(types_IPv6, HandlesBinaryFormat) {
		std::stringstream input;
		input.write((char *)&source[0], source_len);
		Data data = Data(&input);

		IPv6Addr addr = IPv6Addr(&data, 0);

		EXPECT_STREQ("\x01\x02\x03\x04\x05\x06\x07\x08\x09\x0a\x0b\x0c\x0d\x0e\x0f\x10", addr.asBinary().c_str());
	}
};
