
#include "MAC.h"
#include <stdio.h>
#include <string.h>
#include <stdexcept>

MAC::MAC(const Quilt &data, size_t offset)
	: Binary(0)
{
	data.CopyBytesOrFail((char *)(&Binary), offset, 6);
}

std::string MAC::asString() const {
	char r[18];
	snprintf(r, sizeof(r), "%02hhx:%02hhx:%02hhx:%02hhx:%02hhx:%02hhx"
			, (int)(Binary & 0xff)
			, (int)(Binary >> 8) & 0xff
			, (int)(Binary >> 16) & 0xff
			, (int)(Binary >> 24) & 0xff
			, (int)(Binary >> 32) & 0xff
			, (int)(Binary >> 40) & 0xff);
	return (r);

}

unsigned long long MAC::asBinary() const {
	return (Binary);
}

int MAC::compare(const MAC *other) const {
	return (Binary == other->asBinary());
}
