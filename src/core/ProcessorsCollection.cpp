/*
 * ParsersCollection.cpp
 *
 *  Created on: 16 авг. 2016 г.
 *      Author: eugene
 */

#include "ProcessorsCollection.h"

ProcessorsCollection *ProcessorsCollection::p_instance = 0;

std::vector<Processor *> ProcessorsCollection::AsVector()
{
	return (collection);
}
