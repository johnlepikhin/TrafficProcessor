/*
 * Pkt.cpp
 *
 *  Created on: 06 июня 2016 г.
 *      Author: eugene
 */

#include "Data.h"

#include <iostream>
#include <sstream>
#include <stdlib.h>
#include <stdio.h>
#include "../core/utils.h"

Data::Data(std::istream *stream) :
	Size(0),
	Captured (0),
	Position(0)
{
	stream->ignore(8);
	util::anyRead (stream, &Captured, sizeof (Captured));
	util::anyRead (stream, &Size, sizeof (Size));

	size_t dataLength = Captured;
	IS.resize(dataLength, '\0');
	char *begin = &*IS.begin();
	stream->read(begin, (long)dataLength);
}

Data::~Data() {
}

const char *Data::getPtrWithSize(std::streamsize size) {
	const char *ptr = IS.c_str()+Position;
	Position+=(unsigned long)size;
	return (ptr);
}

const char *Data::getPtrAtOffset(std::streamoff offset) const {
	const char *ptr = IS.c_str()+Position+offset;
	return (ptr);
}

const void *Data::readAlloc(std::streamsize size) {
	const char *r = IS.substr(Position, (unsigned long)size).c_str();
	Position+=(unsigned long)size;

	return ((const void *)r);
}

const void *Data::readAllocAhead(std::streamsize size, std::streamoff startpos = 0) const {
	const char *r = IS.substr(Position+(unsigned long)startpos, (unsigned long)size).c_str();

	return ((const void *)r);
}

void Data::read(void *buffer, std::streamsize size) {
	IS.copy((char *)buffer, (unsigned long)size, Position);
	Position+=(unsigned long)size;
}

void Data::readAhead(void *buffer, std::streamsize size, std::streamoff offset = 0) const {
	IS.copy((char *)buffer, (unsigned long)size, Position+(unsigned long)offset);
}

unsigned short Data::read2() {
	unsigned short int r = 0;
	read(&r, 2);

	return (r);
}

unsigned short Data::read2Reverse() {
	unsigned short r = read2 ();

	return (util::reverse2 (r));
}

void Data::ignore(std::streamsize size) {
	Position+=(unsigned long)size;
}

bool Data::compare(std::string orig_string, std::streamsize offset) const {
	long strLen = (long)orig_string.length();
	std::string rdstr((const char *)readAllocAhead(strLen, offset));
	return (0 == orig_string.compare(rdstr));
}

std::streamsize Data::bytesToEnd() const {
	std::streamsize r = (std::streamsize)(IS.length()-Position);
	if (r < 0) {
		return (0);
	} else {
		return (r);
	}
}
