
#include "ProcessorsCollection.h"

ProcessorsCollection *ProcessorsCollection::p_instance = 0;

std::vector<ProcessorTraits *> ProcessorsCollection::AsVector() const
{
	return (collection);
}
