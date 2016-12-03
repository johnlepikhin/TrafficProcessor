// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

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
		void *r = reinterpret_cast<void *>(mallocOrFatal(size));

		stream.read(reinterpret_cast<char *>(r), size);
		if (stream.fail ()) {
			free (r);

			throw std::underflow_error("Stream is empty in mallocRead");
		}

		return (r);
	}

	void anyRead (std::istream &stream, void *ptr, std::streamsize size) {
		stream.read(reinterpret_cast<char *>(ptr), size);

		if (stream.fail ()) {
			throw std::underflow_error("Stream is empty in anyRead");
		}
	}

	unsigned short reverse2 (unsigned short v) {
		return (((v & 0xff) << 8) + (v >> 8));
	}

	uint32_t readToBuffer(int fd, char *buf, uint32_t count) {
		int64_t dataToRead = count;

		while(dataToRead) {
			int64_t rd = read(fd, buf, dataToRead);
			if (rd < 0)
				return (rd);
			if (0 == rd)
				throw std::underflow_error("Stream is empty");
			dataToRead-=rd;
			buf+=rd;
		}

		return (count);
	}

	char skipBuffer[4096];

	uint32_t skipBytesInFD(int fd, uint32_t count) {
		int32_t dataToRead = count;
		while (dataToRead) {
			int32_t bsize = std::min(4096, dataToRead);
			int32_t rd = readToBuffer(fd, skipBuffer, bsize);
			dataToRead-=rd;
		}
		return (count);
	}

	BaseQuilt quiltOfPcap(int fd)
	{
		uint32_t size, captured, secs, usecs;

		readToBuffer (fd, reinterpret_cast<char *>(&secs), sizeof (secs)); //-V206
		readToBuffer (fd, reinterpret_cast<char *>(&usecs), sizeof (usecs)); //-V206
		readToBuffer (fd, reinterpret_cast<char *>(&captured), sizeof (captured)); //-V206
		readToBuffer (fd, reinterpret_cast<char *>(&size), sizeof (size)); //-V206

		std::shared_ptr<std::string> IS = std::make_shared<std::string>();
		IS->resize(captured);
		readToBuffer(fd, &(IS->at(0)), captured);

		BaseQuilt r = std::make_shared<CBaseQuilt>(IS, size, secs, usecs);

		return (r);
	}

	std::string toLower(const std::string &s)
	{
		std::string r;
		r.resize(s.length());
	    for (size_t i = 0; i < s.length(); i++)
	    	r[i]=tolower(s[i]);

	    return (r);
	}

	bool iequals(const std::string& a, const std::string& b)
	{
	    size_t sz = a.size();
	    if (b.size() != sz)
	        return (false);
	    for (size_t i = 0; i < sz; ++i)
	        if (tolower(a[i]) != tolower(b[i]))
	            return (false);
	    return (true);
	}

}
