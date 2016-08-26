
#ifndef DATA_H_
#define DATA_H_

#include <iostream>
#include <sstream>

/**
 * Class that provides functionality to work with raw Pcap frames.
 */
class Data {
public:
	/**
	 * Data constructor.
	 * @param stream Input stream to get Pcap frame from
	 */
	Data (std::istream *stream);

	~Data ();

	/**
	 * Get pointer to current position in buffer, update position according to passed value size.
	 * @param size Length of the expected value
	 * @return Pointer to first byte of value
	 */
	const char *getPtrWithSize (std::streamsize size);

	/**
	 * Get pointer to value at offset. Position in buffer will not be updated.
	 * @param offset Offset relative to current position
	 * @return Pointer to first byte of value
	 */
	const char *getPtrAtOffset (std::streamoff offset) const;

	/**
	 * Read value of specified size, save it to newly allocated memory block and return pointer
	 * to it. Update position in buffer to new offset.
	 * @param size Size of the expected value
	 * @return Pointer to first byte of new value
	 */
	const void *readAlloc (std::streamsize size);

	/**
	 * Read value of specified size at specified offset (relative to current position), save
	 * it to newly allocated memory block and return pointer to it. Position will not be updated.
	 * @param size Size of the expected value
	 * @param offset Offset relative to current position
	 * @return Pointer to first byte of new value
	 */
	const void *readAllocAhead (std::streamsize size, std::streamoff offset) const;

	/**
	 * Read value of specified size, save it to already allocated memory block. Update
	 * position in buffer to new offset.
	 * @param buffer Pointer to output buffer
	 * @param size Size of the expected value
	 */
	void read (void *buffer, std::streamsize size);

	/**
	 * Read value of specified size at specified offset, save it to already allocated
	 * memory block. Position will not be updated.
	 * @param buffer Pointer to output buffer
	 * @param size Size of the expected value
	 * @param offset Offset relative to current position
	 */
	void readAhead (void *buffer, std::streamsize size, std::streamoff offset) const;

	/**
	 * Read byte and return it as unsigned char. Update position in buffer to new offset.
	 * @return Result value
	 */
	unsigned char read1 ();

	/**
	 * Read byte and return it as unsigned char.
	 * @return Result value
	 */
	unsigned char read1Ahead (std::streamoff offset);

	/**
	 * Read two bytes and return it as int. Update position in buffer to new offset.
	 * @return Result value
	 */
	unsigned short read2 ();

	/**
	 * Read two bytes and return it as int. Update position in buffer to new offset.
	 * @return Result value
	 */
	unsigned short read2Ahead (std::streamoff offset);

	/**
	 * Same as Data::read2, but returns bytes in reverse order.
	 * @see Data::read2
	 * @return Result value
	 */
	unsigned short read2Reverse ();

	/**
	 * Skip next N characters (update buffer offset)
	 * @param characters number of characters to skip
	 */
	void ignore (std::streamoff characters);

	/**
	 * Compare string with buffer at specified position.
	 * @param orig_string String to compare with
	 * @param offset Offset in buffer (relative to current position) to compare with
	 * @return Negative int / 0 / positive int
	 */
	bool compare (std::string orig_string, std::streamoff offset) const;

	/**
	 * Returns number of bytes in buffer from current position to the end
	 * @return Number of bytes
	 */
	std::streamsize bytesToEnd () const;

	/**
	 * Total size of captured packet.
	 */
	unsigned int Size;

	/**
	 * Number of captured bytes.
	 */
	unsigned int Captured;

	/**
	 * Input buffer
	 */
	std::string IS;

	/**
	 * Current position in buffer Data::IS
	 */
	unsigned long Position;
};

#endif /* DATA_H_ */
