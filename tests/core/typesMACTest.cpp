#include <gtest/gtest.h>
#include <stdio.h>
#include <stdlib.h>
#include <sstream>
#include <string>
#include <iostream>
#include <iomanip>
#include "../../src/types/Data.h"
#include "../../src/types/MAC.h"

TEST(types_MAC_constructor, HandlesSimpleParser) {
	std::stringstream input;
	input << "00000000\6" << std::string(3, '\000') << "\6" << std::string(3, '\000') << "\xff\xff\xff\xff\xff\xff";
	Data data = Data(&input);
	MAC *mac = new MAC(&data);

	EXPECT_FALSE(NULL == mac);
	delete mac;
}

TEST(types_MAC_constructor, HandlesNULLData) {
	EXPECT_ANY_THROW(MAC(NULL));
}

void handlesEmptyData() {
	std::stringstream input;
	input << "00000000" << std::string(4, '\000') << std::string(4, '\000');
	Data *data = new Data(&input);
	MAC mac = MAC(data);
	delete data;
}

TEST(types_MAC_constructor, HandlesEmptyData) {

	EXPECT_THROW(handlesEmptyData(), std::underflow_error);
}

void handlesInvalidSizeData() {
	std::stringstream input;
	input << "00000000\7" << std::string(3, '\000') << "\7" << std::string(3, '\000');
	Data *data = new Data(&input);
	MAC mac = MAC(data);
	delete data;
}

TEST(types_MAC_constructor, HandlesInvalidSizeData) {

	EXPECT_THROW(handlesInvalidSizeData(), std::underflow_error);
}

TEST(types_MAC, HandlesHumanFormat) {
	std::stringstream input;
	input << "00000000\6" << std::string(3, '\000') << "\6" << std::string(3, '\000') << "\xff\xff\xff\xff\xff\xff";
	Data data = Data(&input);
	MAC *mac = new MAC(&data);

	EXPECT_STREQ("ff:ff:ff:ff:ff:ff", mac->asString().c_str());
	delete mac;
}

TEST(types_MAC, HandlesBinaryFormat) {
	std::stringstream input;
	input << "00000000\6" << std::string(3, '\000') << "\6" << std::string(3, '\000') << "\xff\xff\xff\xff\xff\xff";
	Data data = Data(&input);
	MAC *mac = new MAC(&data);

	EXPECT_STREQ("\xff\xff\xff\xff\xff\xff", mac->asBinary().c_str());
	delete mac;
}
