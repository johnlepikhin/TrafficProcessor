
#include <stdio.h>
#include <stdlib.h>
#include <sstream>
#include <stdexcept>
#include "../types/PhantomQuilt.h"
#include <unistd.h>
#include <memory>

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

	ssize_t readToBuffer(int fd, char *buf, size_t count) {
		ssize_t dataToRead = count;

		while(dataToRead) {
			ssize_t rd = read(fd, buf, dataToRead);
			if (rd < 0)
				return (rd);
			if (0 == rd)
				throw std::underflow_error("Stream is empty");
			dataToRead-=rd;
			buf+=rd;
		}

		return (count);
	}

	ssize_t skipBytesInFD(int fd, size_t count) {
		char buffer[4096];
		return (readToBuffer(fd, buffer, count));
	}

	BaseQuilt quiltOfPcap(int fd)
	{
		unsigned int size, captured, secs, usecs;

		readToBuffer (fd, (char *)&secs, sizeof (secs));
		readToBuffer (fd, (char *)&usecs, sizeof (usecs));
		readToBuffer (fd, (char *)&captured, sizeof (captured));
		readToBuffer (fd, (char *)&size, sizeof (size));

		std::shared_ptr<std::string> IS = std::make_shared<std::string>();
		IS->resize(captured);
		readToBuffer(fd, &(IS->at(0)), captured);

		BaseQuilt r = std::make_shared<CBaseQuilt>(IS, size, secs, usecs);

		return (r);
	}

}
