
#ifndef SRC_TYPES_PROCESSOR_H_
#define SRC_TYPES_PROCESSOR_H_

#include <typeinfo>
#include <RecursiveDelegator.h>
#include "Chunk.h"

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
class Processor : public RecursiveDelegator::Processor<PARENT, THIS>, public ProcessorTraits {
public:
//	static_assert(std::is_base_of<ChunkTraits, THIS>::value || typeid(THIS) == typeid(void), "THIS must be derived from ChunkTraits or be void");

	/**
	 * Base destructor for all processors
	 */
	~Processor()
	{
		try {
			for (auto i : this->Followers) {
				delete i;
			}
			this->Followers.clear();
		} catch (...) {

		}
	}

	virtual void BeforeRecursionHook(THIS *c)
	{
		ChunkTraits *chunk = static_cast<ChunkTraits *>(c);
		chunk->IncrRefs(1);
	}

	virtual void AfterRecursionHook(THIS *c, std::exception *exn, bool found)
	{
		ChunkTraits *chunk = static_cast<ChunkTraits *>(c);
		chunk->DecrRefs(1);
		if (!chunk->RefCounter)
			DestroyChunk(c);
	}

	virtual void DestroyChunk(THIS *chunk)
	{
		delete chunk;
	}
};

#define ASFOLLOWER(PARENT) (Processor<PARENT, void> *)

#endif /* SRC_TYPES_PROCESSOR_H_ */
