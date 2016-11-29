
#ifndef UTILS_H_
#define UTILS_H_

#include <memory>

#include "../types/PhantomQuilt.h"

/**
 * Uncategorized functions
 */
//lint -sem(util::mallocRead, 1p)
//lint -sem(util::anyRead, 1p)
//lint -sem(util::anyRead, 2p)
//lint -sem(util::exitFatal, r_no)
//lint -sem(util::exitMemoryError, r_no)
namespace util {

	/**
	 * Exit immediately with error message
	 * @param msg Error message to show
	 */
	void exitFatal (const char *msg);

	/**
	 * Exit with memory error message
	 */
	void exitMemoryError ();

	/**
	 * malloc() memory of specified size, check if allocation was successful and call
	 * exit_memory() if pointer is NULL. Return pointer to the block otherwise.
	 * @param size Size of block to be allocated
	 * @return Pointer to successfully allocated block
	 */
	void *mallocOrFatal (size_t size);

	/**
	 * mallocOrFatal(size) memory and read bytes from stream into it
	 * @param stream Input stream
	 * @param size Number of bytes to read
	 */
	void *mallocRead (std::istream &stream, std::streamsize size);

	/**
	 * Read arbitrary number of bytes from input stream into specified memory block
	 * @param stream Input stream
	 * @param ptr Pointer to allocated memory block
	 * @param size Number of bytes to read
	 */
	void anyRead (std::istream &stream, void *ptr, std::streamsize size);

	/**
	 * Return 2-byte input value with reversed byte order
	 * @param value Value to reverse
	 * @return Reversed value
	 */
	unsigned short reverse2 (unsigned short value);

	/**
	 * Read bytes into the buffer
	 * @param fd File descriptor
	 * @param buf Pointer to buffer
	 * @param count Number of bytes to read
	 * @return Amount of read bytes
	 */
	ssize_t readToBuffer(int fd, char *buf, size_t count);

	/**
	 * Skip bytes in fd
	 * @param fd File descriptor
	 * @param count Amount of bytes to skip
	 * @return Amount of skipped bytes
	 */
	ssize_t skipBytesInFD(int fd, size_t count);

	/**
	 * Make PCAP quilt string for file descriptor
	 * @param fd File descriptor
	 * @return Quilt representation of PCAP
	 */
	BaseQuilt quiltOfPcap(int fd);

	/**
	 * Case-insensitive string comparsion
	 * @param a String 1
	 * @param b String 2
	 * @return True if strings are equal
	 */
	bool iequals(const std::string& a, const std::string& b);

	/**
	 * Convert string to lowercase
	 * @param s Source string
	 * @return Lowercase version of s
	 */
	std::string toLower(const std::string &s);
}

#endif /* UTILS_H_ */
