
#ifndef IPV4ADDR_H_
#define IPV4ADDR_H_

#include <string>
#include <sparsed-ropes/Quilt.h>

/**
 * IPv4 address container and reader
 */
namespace IPv4Addr {
	/**
	 * Create IPv4 from Data
	 * @param data Pointer to Data
	 * @param offset Offset from where address must be read
	 */
	unsigned long Make(const Quilt &data, const std::streamoff offset);

	unsigned long Make(const std::string &data, const std::streamoff offset);

	/**
	 * Human readable representation
	 * @return Human readable representation
	 */
	std::string asString(unsigned long addr);
};

#endif /* IPV4ADDR_H_ */
