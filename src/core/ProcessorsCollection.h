
#ifndef SRC_CORE_PARSERSCOLLECTION_H_
#define SRC_CORE_PARSERSCOLLECTION_H_

#include <vector>

#include "../types/Processor.h"

/**
 * Stores collection of Processors (singleton)
 */
class ProcessorsCollection {
private:
    std::vector<ProcessorTraits *> collection;

    static ProcessorsCollection * p_instance;
    ProcessorsCollection() {};
	ProcessorsCollection( const ProcessorsCollection& ) {};
	ProcessorsCollection& operator= (const ProcessorsCollection &);
public:

	/**
	 * Returns instanse of singleton
	 * @return Reference to ProcessorsCollection object
	 */
	static ProcessorsCollection *getInstance() {
		if (!p_instance) {
			p_instance = new ProcessorsCollection();
		}
		return (p_instance);
	}

	/**
	 * Adds new Processor to the collection
	 * @param processor Processor to register
	 */
	void Register(ProcessorTraits *processor) {
		collection.push_back(processor);
	}

	/**
	 * Returns the collection as std::vector
	 * @return Vector
	 */
	std::vector<ProcessorTraits *> AsVector() const;
};

#endif /* SRC_CORE_PARSERSCOLLECTION_H_ */
