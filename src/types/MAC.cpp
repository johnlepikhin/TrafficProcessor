
#include "MAC.h"
#include <stdio.h>
#include <string.h>
#include <stdexcept>

namespace MAC {

unsigned long long Make(const Quilt &data, const size_t offset)
{
	unsigned long long mac(0);
	data.CopyBytesOrFail((char *)(&mac), offset, 6);

	return (mac);
}

std::string asString(const unsigned long long mac)
{
	char r[18];
	snprintf(r, sizeof(r), "%02hhx:%02hhx:%02hhx:%02hhx:%02hhx:%02hhx"
			, (int)(mac & 0xff)
			, (int)(mac >> 8) & 0xff
			, (int)(mac >> 16) & 0xff
			, (int)(mac >> 24) & 0xff
			, (int)(mac >> 32) & 0xff
			, (int)(mac >> 40) & 0xff);
	return (r);

}

}
