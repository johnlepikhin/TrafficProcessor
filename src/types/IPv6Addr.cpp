
#include "IPv6Addr.h"
#include <stdio.h>
#include <stdexcept>

IPv6Addr::IPv6Addr(Data *data, std::streamoff offset) {
	if (NULL == data) {
		throw std::invalid_argument("Data is NULL in IPv6 address constructor");
	}

	ptr = data->getPtrAtOffset(offset);
}

std::string IPv6Addr::asString() {
	char r[50];
	snprintf(r, sizeof(r), "%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x",
			(unsigned char)ptr[0],
			(unsigned char)ptr[1],
			(unsigned char)ptr[2],
			(unsigned char)ptr[3],
			(unsigned char)ptr[4],
			(unsigned char)ptr[5],
			(unsigned char)ptr[6],
			(unsigned char)ptr[7],
			(unsigned char)ptr[8],
			(unsigned char)ptr[9],
			(unsigned char)ptr[10],
			(unsigned char)ptr[11],
			(unsigned char)ptr[12],
			(unsigned char)ptr[13],
			(unsigned char)ptr[14],
			(unsigned char)ptr[15]);
	return (r);
}

std::string IPv6Addr::asBinary() {
	return (std::string(ptr, 16));
}

int IPv6Addr::compare(IPv6Addr *other) {
	return (asBinary().compare(other->asBinary()));
}
