
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <sparsed-ropes/Quilt.h>

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

	void *mallocRead (std::istream &stream, std::streamsize size) {
		void *r = (void *)mallocOrFatal((size_t)size);

		stream.read((char *)r, size);
		if (stream.fail ()) {
			free (r);

			throw std::underflow_error("Stream is empty in mallocRead");
		}

		return (r);
	}

	void anyRead (std::istream &stream, void *ptr, std::streamsize size) {
		stream.read((char *)ptr, size);

		if (stream.fail ()) {
			throw std::underflow_error("Stream is empty in anyRead");
		}
	}

	unsigned short reverse2 (unsigned short v) {
		return (((v & 0xff) << 8) + (v >> 8));
	}

	const Quilt *quiltOfPcap(std::istream &stream)
	{
		if (NULL == stream) {
			throw std::invalid_argument("Input stream is NULL");
		}

		unsigned int size, captured;

		stream.ignore(8);
		anyRead (stream, &captured, sizeof (captured));
		anyRead (stream, &size, sizeof (size));

		std::string *IS = new std::string;
		IS->resize(captured, '\0');
		char *begin = &*IS->begin();
		stream.read(begin, (long)captured);
		unsigned long rd = (unsigned long)stream.gcount();
		if (rd < captured) {
			std::stringstream msg;
			msg << "Cannot read announced number of captured bytes: "
				<< captured
				<< ", was read only "
				<< rd;
			throw std::underflow_error(msg.str());
		}

		const Quilt *r = new QuiltSnippet(IS, size);

		return (r);
	}

}
