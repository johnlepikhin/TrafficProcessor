// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "MAC.h"
#include <stdio.h>
#include <string.h>
#include <stdexcept>

namespace MAC {

unsigned long long Make(const std::shared_ptr<Quilt> &data, const size_t offset)
{
	unsigned long long mac(0);
	data->CopyBytesOrFail(reinterpret_cast<char *>(&mac), offset, 6); //-V206

	return (mac);
}

unsigned long long Make(const std::string &data, const size_t offset)
{
	unsigned long long mac;
	data.copy(reinterpret_cast<char *>(&mac), 6, offset); //-V206

	return (mac);
}

std::string asString(const unsigned long long mac)
{
	char r[18];
	snprintf(r, sizeof(r), "%02hhx:%02hhx:%02hhx:%02hhx:%02hhx:%02hhx"
			, static_cast<int>(mac & 0xff)
			, static_cast<int>(mac >> 8) & 0xff
			, static_cast<int>(mac >> 16) & 0xff
			, static_cast<int>(mac >> 24) & 0xff
			, static_cast<int>(mac >> 32) & 0xff //-V112
			, static_cast<int>(mac >> 40) & 0xff);
	return (r);

}

}
