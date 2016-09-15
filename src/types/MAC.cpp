
#include "MAC.h"
#include <stdio.h>
#include <string.h>
#include <stdexcept>

MAC::MAC(const Quilt &data, size_t offset)
{
	Binary.resize(6);
	data.CopyBytesOrFail((char *)Binary.data(), offset, 6);
}

std::string MAC::asString() const {
	char r[18];
	snprintf(r, sizeof(r), "%02hhx:%02hhx:%02hhx:%02hhx:%02hhx:%02hhx",
			Binary[0], Binary[1], Binary[2], Binary[3], Binary[4], Binary[5]);
	return (r);

}

std::string MAC::asBinary() const {
	return (Binary);
}

int MAC::compare(const MAC *other) const {
	return (asBinary().compare(other->asBinary()));
}
