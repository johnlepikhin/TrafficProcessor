// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#include <gtest/gtest.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include "../../src/core/utils.h"
#include <stdexcept>

namespace testUtils {
	TEST(utils_mallocRead, HandlesSimpleReading) {
		std::stringstream *input = new std::stringstream("1234567890");
		char *read_string = (char *)util::mallocRead(input, 5);

		// Binary compare
		EXPECT_TRUE(
				read_string[0]=='1'
				&& read_string[1]=='2'
				&& read_string[2]=='3'
				&& read_string[3]=='4'
				&& read_string[4]=='5'
		);

		delete input;
	}

	void handlesReadingFromEmptyBuffer() {
		std::stringstream *input = new std::stringstream("");
		char *read_string = (char *)util::mallocRead(input, 5);
		free (read_string);
		delete input;
	}

	TEST(utils_mallocRead, HandlesReadingFromEmptyBuffer) {
		EXPECT_THROW(handlesReadingFromEmptyBuffer(), std::underflow_error);
	}

	void handlesReadingFromNULL() {
		char *read_string = (char *)util::mallocRead(NULL, 5);
		free (read_string);
	}


//	TEST(utils_mallocRead, HandlesReadingFromUnitialized) {
//		EXPECT_THROW(handlesReadingFromNULL(), std::invalid_argument);
//	}

	TEST(utils_anyRead, HandlesSimpeReading) {
		std::stringstream *input = new std::stringstream("\xff\xff\xff\xff");
		unsigned short r;
		util::anyRead(input, &r, 2);

		EXPECT_EQ(r, 0xffff);
	}

	TEST(utils_anyRead, HandlesReadingFromEmptyBuffer) {
		std::stringstream *input = new std::stringstream("");
		unsigned short r;

		EXPECT_THROW(util::anyRead(input, &r, 2), std::underflow_error);
	}

//	TEST(utils_anyRead, HandlesReadingFromUninitialized) {
//		unsigned short r;
//
//		EXPECT_THROW(util::anyRead(NULL, &r, 2), std::invalid_argument);
//	}

	TEST(utils_reverse2, HandlesReverse) {
		EXPECT_EQ(util::reverse2(0xaabb), 0xbbaa);
	}
};
