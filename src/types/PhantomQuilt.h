
#ifndef SRC_TYPES_PHANTOMQUILT_H_
#define SRC_TYPES_PHANTOMQUILT_H_

#include <sparsed-ropes/Quilt.h>
#include "Phantom.h"

template <typename SPECIFIER>
class PhantomQuilt : public Phantom<Quilt, SPECIFIER>
{
	using Phantom<Quilt, SPECIFIER>::Phantom;
};

struct SBaseQuilt {};
typedef PhantomQuilt<SBaseQuilt> BaseQuilt;

struct SPayloadQuilt {};
typedef PhantomQuilt<SPayloadQuilt> PayloadQuilt;


#endif /* SRC_TYPES_PHANTOMQUILT_H_ */
