/*
 * utils.cpp
 *
 *  Created on: 06 июня 2016 г.
 *      Author: eugene
 */

#include <stdio.h>
#include <stdlib.h>
#include <iostream>

namespace util {

	void exitFatal (const char *msg) {
		fprintf (stderr, "Fatal error: %s\n", msg);
		exit (1);
	}

	void exitMemoryError () {
		exitFatal ("Cannot allocate memory");
	}

	void *mallocOrFatal (size_t size) {
		void *r = malloc(size);
		if (NULL == r) {
			exitMemoryError();
		}

		return (r);
	}

	void *mallocRead (std::istream *stream, std::streamsize size) {
		void *r = (void *)mallocOrFatal((size_t)size);

		if (NULL == stream) {
			return (NULL);
		}

		stream->read((char *)r, size);
		if (stream->fail ()) {
			free (r);
			return (NULL);
		}

		return (r);
	}

	void anyRead (std::istream *stream, const void *ptr, std::streamsize size) {
		if (NULL == stream) {
			throw -10;
		}

		stream->read((char *)ptr, size);

		if (stream->fail ()) {
			throw -1;
		}
	}

	unsigned short reverse2 (unsigned short v) {
		return (((v & 0xff) << 8) + (v >> 8));
	}
}
