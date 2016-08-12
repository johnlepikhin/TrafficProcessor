/*
 * MAC.h
 *
 *  Created on: 06 июня 2016 г.
 *      Author: eugene
 */

#ifndef MAC_H_
#define MAC_H_

#include <iostream>

#include "../Data.h"

class Data;

/**
 * MAC address container and reader
 */
class MAC {
public:

	/**
	 * Create MAC from Data
	 * @param data Pointer to Data, buffer must point to position from where MAC to read
	 */
	MAC(Data *data);
	~MAC();

	/**
	 * Human readable representation
	 * @return Human readable representation
	 */
	std::string asString();

	/**
	 * Compare with other MAC address
	 * @param other MAC address to compare with
	 * @return Returns an integer < 0 if this MAC is ordered before 'other'
	 *  0 if their values are equivalent, or > 0 if this MAC is ordered after 'other'
	 */
	int compare(MAC *other);

	/**
	 * Binary representation
	 * @return Binary representation
	 */
	std::string asBinary();

private:
	const char *ptr;
};

#endif /* MAC_H_ */
