
#include "MAC.h"
#include <stdio.h>
#include <string.h>
#include <stdexcept>

MAC::MAC(Data *data)
{
	if (NULL == data) {
		throw std::invalid_argument("Data is NULL in MAC constructor");
	}

	ptr = data->getPtrWithSize(6);
}

MAC::~MAC()
{
	ptr = NULL;
}

std::string MAC::asString() const {
	char r[18];
	snprintf(r, sizeof(r), "%02hhx:%02hhx:%02hhx:%02hhx:%02hhx:%02hhx",
			ptr[0], ptr[1], ptr[2], ptr[3], ptr[4], ptr[5]);
	return (r);

}

std::string MAC::asBinary() const {
	return (std::string(ptr, 6));
}

int MAC::compare(const MAC *other) const {
	return (asBinary().compare(other->asBinary()));
}
