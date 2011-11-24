/*
 * BadMove.cc
 *
 *  Created on: Nov 24, 2011
 *      Author: luke
 */

#include "BadMove.hpp"

// initializes to values that indicate they were never initialized

BadMove::BadMove(int row, int col, char illegalInput)
{

}
BadMove::~BadMove()
{

}

const char *BadMove::what()
{
	return "";
}

ostream &BadMove::print(ostream &out)
{

	return out;
}

