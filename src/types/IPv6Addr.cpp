// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "IPv6Addr.h"
#include <stdio.h>
#include <stdexcept>

IPv6Addr::IPv6Addr(const Quilt &data, const std::streamoff offset)
{
	Data.resize(16);
	data.CopyBytesOrFail(&(Data.at(0)), offset, 16);
}

std::string IPv6Addr::AsString() const {
	std::string r;
	r.resize(48, 0);
	uint16_t written = snprintf(&(r.at(0)), 48, "%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x:%02x",
			static_cast<unsigned char>(Data[0]),
			static_cast<unsigned char>(Data[1]),
			static_cast<unsigned char>(Data[2]),
			static_cast<unsigned char>(Data[3]),
			static_cast<unsigned char>(Data[4]), //-V112
			static_cast<unsigned char>(Data[5]),
			static_cast<unsigned char>(Data[6]),
			static_cast<unsigned char>(Data[7]),
			static_cast<unsigned char>(Data[8]),
			static_cast<unsigned char>(Data[9]),
			static_cast<unsigned char>(Data[10]),
			static_cast<unsigned char>(Data[11]),
			static_cast<unsigned char>(Data[12]),
			static_cast<unsigned char>(Data[13]),
			static_cast<unsigned char>(Data[14]),
			static_cast<unsigned char>(Data[15]));
	r.resize(written);
	return (r);
}
