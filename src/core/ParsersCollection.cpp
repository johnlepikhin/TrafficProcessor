/*
 * ParsersCollection.cpp
 *
 *  Created on: 16 авг. 2016 г.
 *      Author: eugene
 */

#include "ParsersCollection.h"

ParsersCollection *ParsersCollection::p_instance = 0;

std::vector<Parser *> ParsersCollection::AsVector()
{
	return (collection);
}
