
#ifndef SRC_TYPES_COUNTER_H_
#define SRC_TYPES_COUNTER_H_

/**
 * Helper class: generate unique sequential IDs
 */
class Counter {
public:
	/**
	 * Constructor
	 */
	Counter() : Value(0) {};

	/**
	 * Get last generated ID
	 */
	inline unsigned long long Get() { return (Value); };

	/**
	 * Returns modulus distance between two IDs
	 * @param v1 ID1
	 * @param v2 ID2
	 */
	inline static unsigned long long Distance(unsigned long long v1, unsigned long long v2) {
		return ((v1 > v2) ? v1-v2 : v2-v1);
	};

	/**
	 * Returns modulus distance between current ID and other ID
	 * @param other Other ID
	 */
	inline unsigned long long Distance(unsigned long long other) {
		return (Distance (other, Value));
	};

	/**
	 * Generate and return next ID
	 */
	inline unsigned long long Next() {
		if (Value == 0xffffffffffffffff) {
			Value=0;
		} else {
			Value++;
		}
		return (Value);
	}
private:
	unsigned long long Value;
};

#endif /* SRC_TYPES_COUNTER_H_ */
