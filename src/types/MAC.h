
#ifndef MAC_H_
#define MAC_H_

#include <iostream>

#include <sparsed-ropes/Quilt.h>

/**
 * MAC address container and reader
 */
class MAC {
public:

	/**
	 * Create MAC from Data
	 * @param data Pointer to Data, buffer must point to position from where MAC to read
	 */
	MAC(const Quilt &data, size_t offset);

	/**
	 * Human readable representation
	 * @return Human readable representation
	 */
	std::string asString() const;

	/**
	 * Compare with other MAC address
	 * @param other MAC address to compare with
	 * @return Returns an integer < 0 if this MAC is ordered before 'other'
	 *  0 if their values are equivalent, or > 0 if this MAC is ordered after 'other'
	 */
	int compare(const MAC *other) const;

	/**
	 * Binary representation
	 * @return Binary representation
	 */
	std::string asBinary() const;

private:
	std::string Binary;
};

#endif /* MAC_H_ */
