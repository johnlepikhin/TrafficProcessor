
#ifndef IPV4ADDR_H_
#define IPV4ADDR_H_

#include <string>
#include "Quilt.h"

/**
 * IPv4 address container and reader
 */
namespace IPv4Addr {
	/**
	 * Create IPv4 from Quilt
	 * @param data Pointer to Quilt
	 * @param offset Offset from where address must be read
	 */
	uint32_t Make(const Quilt &data, const patch_position offset);

	/**
	 * Create IPv4 from std::string
	 * @param data Reference to std::string
	 * @param offset Offset from where address must be read
	 */
	uint32_t Make(const std::string &data, const std::streamoff offset);

	/**
	 * Human readable representation
	 * @return Human readable representation
	 */
	std::string asString(uint32_t addr);
};

#endif /* IPV4ADDR_H_ */
