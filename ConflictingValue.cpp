/*
 * ConflictingValue.cpp
 *
 *  Created on: Nov 24, 2011
 *      Author: luke
 */

#include "ConflictingValue.hpp"

ConflictingValue::ConflictingValue(
		unsigned short int row,
		unsigned short int col,
		char value,
		string message)
:BadMove(row,col,value)
{
	setMessage(message);
}

ConflictingValue::~ConflictingValue()
{

}
const char *ConflictingValue::what()
{
	stringstream ss;
	string ret;
	ss<<"Conflicting Value ["<<row<<","<<col<<"] ("<<illegalInput<<"): "
			<<information;
	ret = ss.str();
	return ret.c_str();
}
ostream& ConflictingValue::print(ostream &out)
{
	out<<what();
}
