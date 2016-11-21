
#ifndef SRC_TYPES_PHANTOMQUILT_H_
#define SRC_TYPES_PHANTOMQUILT_H_

#include <memory>
#include <sparsed-ropes/Quilt.h>
#include "Phantom.h"

template <typename SPECIFIER>
class PhantomQuilt : public Phantom<Quilt, SPECIFIER>
{
	using Phantom<Quilt, SPECIFIER>::Phantom;
};

class CBaseQuilt : public Quilt {
public:
	CBaseQuilt(std::shared_ptr<const std::string> data
			, const patch_position length
			, unsigned int secs
			, unsigned int usecs);

	unsigned int Seconds;
	unsigned int USeconds;
};

struct __BaseQuilt {};
typedef std::shared_ptr<CBaseQuilt> BaseQuilt;

struct __PayloadQuilt {};
typedef PhantomQuilt<__PayloadQuilt> CPayloadQuilt;
typedef std::shared_ptr<CPayloadQuilt> PayloadQuilt;


#endif /* SRC_TYPES_PHANTOMQUILT_H_ */
