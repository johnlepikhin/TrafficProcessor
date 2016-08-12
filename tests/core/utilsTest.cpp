#include <gtest/gtest.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include "../../src/core/utils.h"

TEST(mallocReadTest, HandlesSimpleReading) {
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
}
