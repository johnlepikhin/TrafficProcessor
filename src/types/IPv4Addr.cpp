
#include <stdio.h>
#include <stdexcept>

#include "IPv4Addr.h"

namespace IPv4Addr {

unsigned long Make(const Quilt &data, const std::streamoff offset)
{
	unsigned long addr(0);
	data.CopyBytesOrFail((char *)&addr, offset, 4);
	return (addr);
}

std::string asString(unsigned long addr)
{
	std::string r;
	r.resize(16, 0);
	snprintf(&(r.at(0)), 16, "%i.%i.%i.%i",
			(int)(addr & 0xff),
			(int)((addr >> 8) & 0xff),
			(int)((addr >> 16) & 0xff),
			(int)(addr >> 24));
	return (r);
}

}
