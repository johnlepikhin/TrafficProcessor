
#include "ProcessorsCollection.h"

ProcessorsCollection *ProcessorsCollection::p_instance = 0;

std::vector<Processor *> ProcessorsCollection::AsVector() const
{
	return (collection);
}
