
#include <stdio.h>
#include <stdexcept>

#include "IPv4Addr.h"

IPv4Addr::IPv4Addr(const Quilt &data, std::streamoff offset) {
	Binary.resize(4);
	data.CopyBytesOrFail((char *)Binary.data(), offset, 4);
}

std::string IPv4Addr::asString() const {
	char r[16];
	snprintf(r, sizeof(r), "%i.%i.%i.%i",
			(unsigned char)Binary[0],
			(unsigned char)Binary[1],
			(unsigned char)Binary[2],
			(unsigned char)Binary[3]);
	return (r);
}

std::string IPv4Addr::asBinary() const {
	return (Binary);
}

unsigned int IPv4Addr::asInt() const
{
	return ((Binary[0] << 24) + (Binary[1] << 16) + (Binary[2] << 8) + Binary[3]);
}

int IPv4Addr::compare(IPv4Addr *other) {
	return (asBinary().compare(other->asBinary()));
}
