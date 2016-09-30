
#ifndef SRC_TYPES_PHANTOMQUILT_H_
#define SRC_TYPES_PHANTOMQUILT_H_

#include <sparsed-ropes/Quilt.h>
#include "Phantom.h"

template <typename SPECIFIER>
class PhantomQuilt : public Phantom<Quilt, SPECIFIER>
{
	using Phantom<Quilt, SPECIFIER>::Phantom;
};

struct __BaseQuilt {};
typedef PhantomQuilt<__BaseQuilt> CBaseQuilt;
typedef std::shared_ptr<CBaseQuilt> BaseQuilt;

struct __PayloadQuilt {};
typedef PhantomQuilt<__PayloadQuilt> CPayloadQuilt;
typedef std::shared_ptr<CPayloadQuilt> PayloadQuilt;


#endif /* SRC_TYPES_PHANTOMQUILT_H_ */
