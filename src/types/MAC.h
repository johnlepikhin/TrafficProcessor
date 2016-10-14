
#ifndef MAC_H_
#define MAC_H_

#include <sparsed-ropes/Quilt.h>

/**
 * MAC address container and reader
 */
namespace MAC {
	/**
	 * Create MAC from Data
	 * @param data Pointer to Data, buffer must point to position from where MAC to read
	 */
	unsigned long long Make(std::shared_ptr<Quilt> data, const size_t offset);

	/**
	 * Create MAC from substring
	 * @param data string from where MAC to read
	 */
	unsigned long long Make(const std::string &data, const size_t offset);

	/**
	 * Human readable representation
	 * @return Human readable representation
	 */
	std::string asString(const unsigned long long mac);
};

#endif /* MAC_H_ */
