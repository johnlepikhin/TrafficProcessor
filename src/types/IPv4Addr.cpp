
#include <stdio.h>
#include <stdexcept>

#include "IPv4Addr.h"

IPv4Addr::IPv4Addr(const Quilt &data, std::streamoff offset)
	: Binary(0)
{
	data.CopyBytesOrFail((char *)&Binary, offset, 4);
}

std::string IPv4Addr::asString() const {
	char r[16];
	snprintf(r, sizeof(r), "%i.%i.%i.%i",
			(Binary & 0xff),
			((Binary >> 8) & 0xff),
			((Binary >> 16) & 0xff),
			(Binary >> 24));
	return (r);
}

int IPv4Addr::compare(IPv4Addr *other) {
	return (Binary == other->Binary);
}
