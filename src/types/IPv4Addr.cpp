
#include <stdio.h>
#include <stdexcept>

#include "IPv4Addr.h"

namespace IPv4Addr {

unsigned long Make(Quilt &data, const patch_position offset)
{
	unsigned long addr(0);
	data.CopyBytesOrFail((char *)&addr, offset, 4);
	return (addr);
}

unsigned long Make(const std::string &data, const std::streamoff offset)
{
	unsigned long addr(0);
	data.copy((char *)&addr, 4, offset);
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
