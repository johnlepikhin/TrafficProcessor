
#ifndef IPV6ADDR_H_
#define IPV6ADDR_H_

#include <string>
#include <sparsed-ropes/Quilt.h>

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
	IPv6Addr(const Quilt &data, const std::streamoff offset);

	/**
	 * Human readable representation
	 * @return Human readable representation
	 */
	std::string AsString() const;

	/**
	 * Binary representation
	 * @return Binary representation
	 */
	inline std::string AsBinary() const { return (Data); };
	inline bool operator=(IPv6Addr &other) const { return (Data == other.AsBinary()); }
private:
	std::string Data;
};

#endif
