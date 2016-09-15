/*
 * utils.h
 *
 *  Created on: 06 июня 2016 г.
 *      Author: eugene
 */

#ifndef UTILS_H_
#define UTILS_H_

#include <istream>

#include "sparsed-ropes/Quilt.h"

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

	const Quilt *quiltOfPcap(std::istream &stream);
}

#endif /* UTILS_H_ */
