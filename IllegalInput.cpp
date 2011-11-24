/*
 * IllegalInput.cc
 *
 *  Created on: Nov 24, 2011
 *      Author: luke
 */

#include "IllegalInput.hpp"

IllegalInput::IllegalInput(unsigned short int row, unsigned short int col,
		char value, string message)
:BadMove(row,col,value)
{
	setMessage(message);
}

IllegalInput::~IllegalInput()
{

}

const char *IllegalInput::what()
{
	stringstream ss;
	string ret;
	ss<<"Illegal Input ["<<row+1<<","<<col+1<<"] ("<<illegalInput<<"): "
			<<information;
	ret = ss.str();
	return ret.c_str();

}
ostream& IllegalInput::print(ostream &out)
{
	out<<what();
	return out;
}
