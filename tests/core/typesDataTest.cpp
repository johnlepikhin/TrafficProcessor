#include <gtest/gtest.h>
#include <stdio.h>
#include <stdlib.h>
#include <sstream>
#include <string>
#include <iostream>
#include <iomanip>
#include "../../src/types/Data.h"

TEST(types_Data_constructor, HandlesSimpleConstructor) {
	std::stringstream input;
	input << "00000000\6" << std::string(3, '\000') << "\6" << std::string(3, '\000') << "\xff\xff\xff\xff\xff\xff";
	Data *data = new Data(&input);

	EXPECT_FALSE(NULL == data);
	delete data;
}

TEST(types_Data_constructor, HandlesNULLData) {
	EXPECT_ANY_THROW(Data(NULL));
}

void handlesEmptyInput() {
	std::stringstream input;
	Data data = Data(&input);
}

TEST(types_Data_constructor, HandlesEmptyInput) {

	EXPECT_THROW(handlesEmptyInput(), std::underflow_error);
}

void handlesInvalidSize() {
	std::stringstream input;
	input << "00000000\7" << std::string(3, '\000') << "\7" << std::string(3, '\000');
	Data data = Data(&input);
}

TEST(types_Data_constructor, HandlesInvalidSizeData) {
	EXPECT_THROW(handlesInvalidSize(), std::underflow_error);
}

TEST(types_Data, HandlesGetPtrWithSizeSimple) {
	std::stringstream input;
	input << "00000000\6" << std::string(3, '\000') << "\6" << std::string(3, '\000') << "\xff\xff\xff\xff\xff\xff";
	Data data = Data(&input);
	EXPECT_EQ(data.getPtrWithSize(6)[0], '\xff');
}

TEST(types_Data, HandlesGetPtrWithInvalidSize) {
	std::stringstream input;
	input << "00000000\6" << std::string(3, '\000') << "\6" << std::string(3, '\000') << "\xff\xff\xff\xff\xff\xff";
	Data data = Data(&input);
	EXPECT_THROW(data.getPtrWithSize(300), std::underflow_error);
}

TEST(types_Data, HandlesGetPtrAtOffsetSimple) {
	std::stringstream input;
	input << "00000000\6" << std::string(3, '\000') << "\6" << std::string(3, '\000') << "\x11\x22\x33\x44\x55\x66";
	Data data = Data(&input);
	EXPECT_EQ(data.getPtrAtOffset(3)[0], '\x44');
}

TEST(types_Data, HandlesGetPtrAtInvalidOffset) {
	std::stringstream input;
	input << "00000000\6" << std::string(3, '\000') << "\6" << std::string(3, '\000') << "\xff\xff\xff\xff\xff\xff";
	Data data = Data(&input);
	EXPECT_THROW(data.getPtrAtOffset(300), std::underflow_error);
}

TEST(types_Data, HandlesReadAlloc) {
	std::stringstream input;
	input << "00000000\6" << std::string(3, '\000') << "\6" << std::string(3, '\000') << "\xff\xff\xff\xff\xff\xff";
	Data data = Data(&input);
	char *rd = (char *)data.readAlloc(3);
	EXPECT_STREQ(rd, "\xff\xff\xff");
}

TEST(types_Data, HandlesReadAllocInvalidSize) {
	std::stringstream input;
	input << "00000000\6" << std::string(3, '\000') << "\6" << std::string(3, '\000') << "\xff\xff\xff\xff\xff\xff";
	Data data = Data(&input);
	EXPECT_THROW(data.readAlloc(300), std::underflow_error);
}

TEST(types_Data, HandlesReadAllocAhead) {
	std::stringstream input;
	input << "00000000\6" << std::string(3, '\000') << "\6" << std::string(3, '\000') << "\xff\xff\xff\xff\xff\xff";
	Data data = Data(&input);
	char *rd = (char *)data.readAllocAhead(3, 2);
	EXPECT_STREQ(rd, "\xff\xff\xff");
}

TEST(types_Data, HandlesReadAllocAheadInvalidSize) {
	std::stringstream input;
	input << "00000000\6" << std::string(3, '\000') << "\6" << std::string(3, '\000') << "\xff\xff\xff\xff\xff\xff";
	Data data = Data(&input);
	EXPECT_THROW(data.readAllocAhead(300, 2), std::underflow_error);
}

TEST(types_Data, HandlesReadAllocAheadInvalidOffset) {
	std::stringstream input;
	input << "00000000\6" << std::string(3, '\000') << "\6" << std::string(3, '\000') << "\xff\xff\xff\xff\xff\xff";
	Data data = Data(&input);
	EXPECT_THROW(data.readAllocAhead(3, 300), std::underflow_error);
}



TEST(types_Data, HandlesRead) {
	std::stringstream input;
	input << "00000000\6" << std::string(3, '\000') << "\6" << std::string(3, '\000') << "\xff\xff\xff\xff\xff\xff";
	Data data = Data(&input);
	char *rd = (char *)malloc(4);
	rd[3]=0;
	data.read(rd, 3);
	EXPECT_STREQ(rd, "\xff\xff\xff");
	free (rd);
}

TEST(types_Data, HandlesReadInvalidSize) {
	std::stringstream input;
	input << "00000000\6" << std::string(3, '\000') << "\6" << std::string(3, '\000') << "\xff\xff\xff\xff\xff\xff";
	Data data = Data(&input);
	char *rd = (char *)malloc(301);
	EXPECT_THROW(data.read(rd, 300), std::underflow_error);
	free (rd);
}

TEST(types_Data, HandlesReadAhead) {
	std::stringstream input;
	input << "00000000\6" << std::string(3, '\000') << "\6" << std::string(3, '\000') << "\xff\xff\xff\xff\xff\xff";
	Data data = Data(&input);
	char *rd = (char *)malloc(4);
	rd[3]=0;
	data.readAhead(rd, 3, 2);
	EXPECT_STREQ(rd, "\xff\xff\xff");
	free (rd);
}

TEST(types_Data, HandlesReadAheadInvalidSize) {
	std::stringstream input;
	input << "00000000\6" << std::string(3, '\000') << "\6" << std::string(3, '\000') << "\xff\xff\xff\xff\xff\xff";
	Data data = Data(&input);
	char *rd = (char *)malloc(301);
	EXPECT_THROW(data.readAhead(rd, 300, 2), std::underflow_error);
	free (rd);
}

TEST(types_Data, HandlesReadAheadInvalidOffset) {
	std::stringstream input;
	input << "00000000\6" << std::string(3, '\000') << "\6" << std::string(3, '\000') << "\xff\xff\xff\xff\xff\xff";
	Data data = Data(&input);
	char *rd = (char *)malloc(301);
	EXPECT_THROW(data.readAhead(rd, 3, 300), std::underflow_error);
	free (rd);
}


TEST(types_Data, HandlesRead2) {
	std::stringstream input;
	input << "00000000\6" << std::string(3, '\000') << "\6" << std::string(3, '\000') << "\xaa\xbb\xcc\xdd\xee\xff";
	Data data = Data(&input);
	EXPECT_EQ(data.read2(), 0xbbaa);
}

TEST(types_Data, HandlesRead2Reverse) {
	std::stringstream input;
	input << "00000000\6" << std::string(3, '\000') << "\6" << std::string(3, '\000') << "\xaa\xbb\xcc\xdd\xee\xff";
	Data data = Data(&input);
	EXPECT_EQ(data.read2Reverse(), 0xaabb);
}

TEST(types_Data, HandlesIgnore) {
	std::stringstream input;
	input << "00000000\6" << std::string(3, '\000') << "\6" << std::string(3, '\000') << "\xaa\xbb\xcc\xdd\xee\xff";
	Data data = Data(&input);
	data.ignore(2);
	EXPECT_EQ(data.read2(), 0xddcc);
}

TEST(types_Data, HandlesCompare) {
	std::stringstream input;
	input << "00000000\6" << std::string(3, '\000') << "\6" << std::string(3, '\000') << "\xaa\xbb\xcc\xdd\xee\xff";
	Data data = Data(&input);
	std::string orig_str = "\xbb\xcc";
	EXPECT_TRUE(data.compare(orig_str, 1));
}

TEST(types_Data, HandlesBytesToEnd) {
	std::stringstream input;
	input << "00000000\6" << std::string(3, '\000') << "\6" << std::string(3, '\000') << "\xaa\xbb\xcc\xdd\xee\xff";
	Data data = Data(&input);
	EXPECT_EQ(data.bytesToEnd(), 6);
}

