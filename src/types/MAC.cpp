/*
 * MAC.cpp
 *
 *  Created on: 06 июня 2016 г.
 *      Author: eugene
 */

#include "MAC.h"
#include "../core/utils.h"
#include <stdio.h>
#include <string.h>

MAC::MAC(Data *data)
	: ptr(data->getPtrWithSize(6))
{
}

std::string MAC::asString() {
	char r[18];
	snprintf(r, sizeof(r), "%02hhx:%02hhx:%02hhx:%02hhx:%02hhx:%02hhx",
			ptr[0], ptr[1], ptr[2], ptr[3], ptr[4], ptr[5]);
	return (r);

}

std::string MAC::asBinary() {
	return (std::string(ptr, 6));
}

int MAC::compare(MAC *other) {
	return (asBinary().compare(other->asBinary()));
}
