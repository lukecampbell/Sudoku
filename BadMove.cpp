/*
 * BadMove.cc
 *
 *  Created on: Nov 24, 2011
 *      Author: luke
 */

#include "BadMove.hpp"


// initializes to values that indicate they were never initialized

BadMove::BadMove(unsigned short int row, unsigned short int col,
		char illegalInput)
:row(row), col(col), illegalInput(illegalInput)
{

}
BadMove::~BadMove()
{
}

const char *BadMove::what() const
{
	return information.c_str();
}

ostream &BadMove::print(ostream &out)
{

	return out;
}

void BadMove::setMessage(const string& message)
{
	information = message;
}

void BadMove::setRow(unsigned short int row)
{
	this->row = row;
}

void BadMove::setCol(unsigned short int col)
{
	this->col = col;
}

void BadMove::setValue(char value)
{
	this->illegalInput = value;
}

unsigned short int BadMove::getRow() const
{
	return row;
}
unsigned short int BadMove::getCol() const
{
	return col;
}
char BadMove::getValue() const
{
	return illegalInput;
}
string BadMove::getMessage() const
{
	return information;
}
