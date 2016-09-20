
#ifndef IPV4ADDR_H_
#define IPV4ADDR_H_

#include <string>
#include <sparsed-ropes/Quilt.h>

/**
 * IPv4 address container and reader
 */
class IPv4Addr {
public:
	/**
	 * Create IPv4 from Data
	 * @param data Pointer to Data
	 * @param offset Offset from where address must be read
	 */
	IPv4Addr(const Quilt &data, std::streamoff offset);

	/**
	 * Human readable representation
	 * @return Human readable representation
	 */
	std::string asString() const;

	/**
	 * Compare with other IPv4 address
	 * @param other IPv4 address to compare with
	 * @return Returns an integer < 0 if this IPv4 is ordered before 'other'
	 *  0 if their values are equivalent, or > 0 if this IPv4 is ordered after 'other'
	 */
	int compare(IPv4Addr *);

	/**
	 * Binary representation
	 * @return Binary representation
	 */
	std::string asBinary() const;

	unsigned int asInt() const;
private:
	std::string Binary;
};

#endif /* IPV4ADDR_H_ */
