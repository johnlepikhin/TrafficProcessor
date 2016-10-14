
#ifndef SRC_TYPES_COUNTER_H_
#define SRC_TYPES_COUNTER_H_

class Counter {
public:
	Counter() : Value(0) {};

	inline unsigned long long Get() { return (Value); };

	inline static unsigned long long Distance(unsigned long long v1, unsigned long long v2) {
		return ((v1 > v2) ? v1-v2 : v2-v1);
	};

	inline unsigned long long Distance(unsigned long long other) {
		return (Distance (other, Value));
	};

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
