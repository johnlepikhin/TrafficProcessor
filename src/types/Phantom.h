
#ifndef SRC_TYPES_PHANTOM_H_
#define SRC_TYPES_PHANTOM_H_

template <typename DATA, typename SPECIFIER>
class Phantom : public DATA {
	using DATA::DATA;
};

#endif /* SRC_TYPES_PHANTOM_H_ */
