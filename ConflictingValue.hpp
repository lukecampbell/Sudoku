/*
 * ConflictingValue.hpp
 *
 *  Created on: Nov 24, 2011
 *      Author: luke
 */

#ifndef CONFLICTINGVALUE_HPP_
#define CONFLICTINGVALUE_HPP_

#include "BadMove.hpp"

class ConflictingValue : public BadMove
{
public:
	ConflictingValue();
	virtual ~ConflictingValue();
	virtual const char *what();
	virtual ostream& print(ostream &out);
};


#endif /* CONFLICTINGVALUE_HPP_ */
