
#ifndef SRC_TYPES_PROCESSOR_H_
#define SRC_TYPES_PROCESSOR_H_

#include <typeinfo>
#include <RecursiveDelegator.h>
#include "Chunk.h"

/**
 * Traits for all public processors
 */
class ProcessorTraits {
public:
	virtual ~ProcessorTraits() {};

	/**
	 * Returns unique ID for this Processor
	 * @return ID
	 */
	virtual std::string ID() = 0;

	/**
	 * Returns description for the Processor
	 * @return Description
	 */
	virtual std::string Description() = 0;
};

/**
 * Base class for processors of all types
 */
template<typename PARENT, typename THIS>
class Processor
		: public RecursiveDelegator::Processor<PARENT, THIS>
		, public ProcessorTraits
{
public:
	typedef PARENT PARENT_T;
	typedef THIS THIS_T;

	Processor<PARENT, void> *AsFollower() { return(reinterpret_cast<Processor<PARENT, void> *>(this)); }
};

#endif /* SRC_TYPES_PROCESSOR_H_ */
