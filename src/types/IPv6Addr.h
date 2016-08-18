
#ifndef IPV6ADDR_H_
#define IPV6ADDR_H_

#include <string>
#include "Data.h"

/**
 * IPv6 address container and reader
 */
class IPv6Addr {
public:
	/**
	 * Create IPv6 from Data
	 * @param data Pointer to Data
	 * @param offset Offset from where address must be read
	 */
	IPv6Addr(Data *data, std::streamoff offset);

	/**
	 * Human readable representation
	 * @return Human readable representation
	 */
	std::string asString() const;

	/**
	 * Compare with other IPv6 address
	 * @param other IPv6 address to compare with
	 * @return Returns an integer < 0 if this IPv6 is ordered before 'other'
	 *  0 if their values are equivalent, or > 0 if this IPv6 is ordered after 'other'
	 */
	int compare(IPv6Addr *);

	/**
	 * Binary representation
	 * @return Binary representation
	 */
std::string asBinary() const;
private:
	const char *ptr;
};

#endif
