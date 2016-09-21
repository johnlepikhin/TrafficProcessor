
#include <stdio.h>
#include <stdexcept>

#include "IPv4Addr.h"

IPv4Addr::IPv4Addr(const Quilt &data, std::streamoff offset) {
	data.CopyBytesOrFail((char *)&Binary, offset, 4);
}

std::string IPv4Addr::asString() const {
	char r[16];
	snprintf(r, sizeof(r), "%i.%i.%i.%i",
			(unsigned char)(Binary >> 24),
			(unsigned char)((Binary >> 16) & 0xf),
			(unsigned char)((Binary >> 8) & 0xf),
			(unsigned char)(Binary & 0xf));
	return (r);
}

int IPv4Addr::compare(IPv4Addr *other) {
	return (Binary == other->Binary);
}
