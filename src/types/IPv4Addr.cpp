// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include <stdio.h>
#include <stdexcept>

#include "IPv4Addr.h"

namespace IPv4Addr {

uint32_t Make(const Quilt &data, const patch_position offset)
{
	uint32_t addr(0);
	data.CopyBytesOrFail(reinterpret_cast<char *>(&addr) //-V206
			, offset, 4); //-V112
	return (addr);
}

uint32_t Make(const std::string &data, const std::streamoff offset)
{
	uint32_t addr(0);
	data.copy(reinterpret_cast<char *>(&addr) //-V206
			, 4, offset); //-V112
	return (addr);
}

std::string asString(uint32_t addr)
{
	std::string r;
	r.resize(16, 0);
	uint16_t written = snprintf(&(r.at(0)), 16, "%i.%i.%i.%i",
			static_cast<int>(addr & 0xff),
			static_cast<int>((addr >> 8) & 0xff),
			static_cast<int>((addr >> 16) & 0xff),
			static_cast<int>(addr >> 24));
	r.resize(written);
	return (r);
}

}
