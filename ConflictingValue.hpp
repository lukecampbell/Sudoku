/*
 * ConflictingValue.hpp
 *
 *  Created on: Nov 24, 2011
 *      Author: luke
 */

#ifndef CONFLICTINGVALUE_HPP_
#define CONFLICTINGVALUE_HPP_

#include <sstream>
#include "BadMove.hpp"


class ConflictingValue : public BadMove
{
public:
	ConflictingValue(unsigned short int row=-1,
			unsigned short int col=-1,
			char value='\0',
			string message="");
	virtual ~ConflictingValue();
	virtual const char *what();
	virtual ostream& print(ostream &out);
};
inline ostream& operator<<(ostream& out, ConflictingValue &cv)
{
	return cv.print(out);
}

#endif /* CONFLICTINGVALUE_HPP_ */
