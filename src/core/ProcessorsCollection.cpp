// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "ProcessorsCollection.h"

ProcessorsCollection *ProcessorsCollection::p_instance = 0;

std::vector<ProcessorTraits *> ProcessorsCollection::AsVector() const
{
	return (collection);
}
