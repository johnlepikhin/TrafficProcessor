
#include "Data.h"

#include <iostream>
#include <sstream>
#include <stdlib.h>
#include <stdio.h>
#include <stdexcept>
#include "../core/utils.h"

Data::Data(std::istream *stream) :
	Size(0),
	Captured (0),
	Position(0)
{
	if (NULL == stream) {
		throw std::invalid_argument("Input stream is NULL");
	}

	stream->ignore(8);
	util::anyRead (stream, &Captured, sizeof (Captured));
	util::anyRead (stream, &Size, sizeof (Size));

	IS.resize(Captured, '\0');
	char *begin = &*IS.begin();
	stream->read(begin, (long)Captured);
	unsigned long rd = (unsigned long)stream->gcount();
	if (rd < Captured) {
		std::stringstream msg;
		msg << "Cannot read announced number of captured bytes: "
			<< Captured
			<< ", was read only "
			<< rd;
		throw std::underflow_error(msg.str());
	}
}

Data::~Data() {
}

const char *Data::getPtrWithSize(std::streamsize size) {
	if (Position+(unsigned long)size > IS.length()) {
		throw std::underflow_error("Data is underflow");
	}

	const char *ptr = IS.c_str()+Position;
	Position+=(unsigned long)size;
	return (ptr);
}

const char *Data::getPtrAtOffset(std::streamoff offset) const {
	if (Position+(unsigned long)offset >= IS.length()) {
		throw std::underflow_error("Data is underflow");
	}

	const char *ptr = IS.c_str()+Position+offset;
	return (ptr);
}

const void *Data::readAlloc(std::streamsize size) {
	if (Position+(unsigned long)size > IS.length()) {
		throw std::underflow_error("Data is underflow");
	}

	const char *r = IS.substr(Position, (unsigned long)size).c_str();
	Position+=(unsigned long)size;

	return ((const void *)r);
}

const void *Data::readAllocAhead(std::streamsize size, std::streamoff startpos = 0) const {
	if (Position+(unsigned long)startpos+(unsigned long)size > IS.length()) {
		throw std::underflow_error("Data is underflow");
	}

	const char *r = IS.substr(Position+(unsigned long)startpos, (unsigned long)size).c_str();

	return ((const void *)r);
}

void Data::read(void *buffer, std::streamsize size) {
	if (Position+(unsigned long)size > IS.length()) {
		throw std::underflow_error("Data is underflow");
	}

	IS.copy((char *)buffer, (unsigned long)size, Position);
	Position+=(unsigned long)size;
}

void Data::readAhead(void *buffer, std::streamsize size, std::streamoff offset = 0) const {
	if (Position+(unsigned long)offset+(unsigned long)size > IS.length()) {
		throw std::underflow_error("Data is underflow");
	}

	IS.copy((char *)buffer, (unsigned long)size, Position+(unsigned long)offset);
}

unsigned char Data::read1() {
	unsigned char r = 0;

	read(&r, 1);

	return (r);
}

unsigned char Data::read1Ahead(std::streamoff offset) {
	unsigned char r = 0;

	readAhead(&r, 1, offset);

	return (r);
}

unsigned short Data::read2() {
	unsigned short int r = 0;

	read(&r, 2);

	return (r);
}

unsigned short Data::read2Ahead(std::streamoff offset) {
	unsigned short r = 0;

	readAhead(&r, 2, offset);

	return (r);
}

unsigned short Data::read2Reverse() {
	unsigned short r = read2 ();

	return (util::reverse2 (r));
}

void Data::ignore(std::streamsize size) {
	if (Position+(unsigned long)size > IS.length()) {
		throw std::underflow_error("Data is underflow");
	}

	Position+=(unsigned long)size;
}

bool Data::compare(std::string orig_string, std::streamsize offset) const {
	long strLen = (long)orig_string.length();

	if (Position+(unsigned long)offset+(unsigned long)strLen > IS.length()) {
		throw std::underflow_error("Data is underflow");
	}

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
