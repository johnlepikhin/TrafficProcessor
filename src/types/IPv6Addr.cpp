
#include "IPv6Addr.h"
#include <stdio.h>
#include <stdexcept>

IPv6Addr::IPv6Addr(const Quilt &data, const std::streamoff offset)
{
	Data.resize(16);
	data.CopyBytesOrFail(&(Data.at(0)), offset, 16);
}

std::string IPv6Addr::AsString() const {
	char r[50];
	snprintf(r, sizeof(r), "%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x",
			(unsigned char)Data.at(0),
			(unsigned char)Data.at(1),
			(unsigned char)Data.at(2),
			(unsigned char)Data.at(3),
			(unsigned char)Data.at(4),
			(unsigned char)Data.at(5),
			(unsigned char)Data.at(6),
			(unsigned char)Data.at(7),
			(unsigned char)Data.at(8),
			(unsigned char)Data.at(9),
			(unsigned char)Data.at(10),
			(unsigned char)Data.at(11),
			(unsigned char)Data.at(12),
			(unsigned char)Data.at(13),
			(unsigned char)Data.at(14),
			(unsigned char)Data.at(15));
	return (r);
}
