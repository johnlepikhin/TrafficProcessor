
#include "MAC.h"
#include <stdio.h>
#include <string.h>
#include <stdexcept>

MAC::MAC(const Quilt &data, size_t offset)
	: Binary(0)
{
	data.CopyBytesOrFail((char *)(&Binary)+2, offset, 6);
}

std::string MAC::asString() const {
	char r[18];
	snprintf(r, sizeof(r), "%02hhx:%02hhx:%02hhx:%02hhx:%02hhx:%02hhx"
			, (int)(Binary >> 40) & 0xf
			, (int)(Binary >> 32) & 0xf
			, (int)(Binary >> 24) & 0xf
			, (int)(Binary >> 16) & 0xf
			, (int)(Binary >> 8) & 0xf
			, (int)(Binary & 0xf));
	return (r);

}

unsigned long long MAC::asBinary() const {
	return (Binary);
}

int MAC::compare(const MAC *other) const {
	return (Binary == other->asBinary());
}
