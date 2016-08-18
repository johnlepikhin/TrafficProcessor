
#include <stdio.h>
#include <stdexcept>

#include "IPv4Addr.h"

IPv4Addr::IPv4Addr(Data *data, std::streamoff offset) {
	if (NULL == data) {
		throw std::invalid_argument("Data is NULL in IPv6 address constructor");
	}

	ptr = data->getPtrAtOffset(offset);
}

std::string IPv4Addr::asString() const {
	char r[16];
	snprintf(r, sizeof(r), "%i.%i.%i.%i",
			(unsigned char)ptr[0],
			(unsigned char)ptr[1],
			(unsigned char)ptr[2],
			(unsigned char)ptr[3]);
	return (r);
}

std::string IPv4Addr::asBinary() const {
	return (std::string(ptr, 4));
}

int IPv4Addr::compare(IPv4Addr *other) {
	return (asBinary().compare(other->asBinary()));
}
