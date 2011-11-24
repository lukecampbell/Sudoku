/*
 * IllegalInput.hpp
 *
 *  Created on: Nov 24, 2011
 *      Author: luke
 */



#ifndef ILLEGALINPUT_HPP_
#define ILLEGALINPUT_HPP_

#include "BadMove.hpp"


class IllegalInput : public BadMove
{
public:
	IllegalInput();
	virtual ~IllegalInput();
	virtual const char *what();
	virtual ostream& print(ostream &out);
};

#endif /* ILLEGALINPUT_HPP_ */
