/*
 * IllegalInput.hpp
 *
 *  Created on: Nov 24, 2011
 *      Author: luke
 */



#ifndef ILLEGALINPUT_HPP_
#define ILLEGALINPUT_HPP_
#include <sstream>
#include "BadMove.hpp"


class IllegalInput : public BadMove
{
public:
	IllegalInput(unsigned short int row=-1,
			unsigned short int col=-1,
			char value='\0',
			string message="");
	virtual ~IllegalInput();
	virtual const char *what();
	virtual ostream& print(ostream &out);
};
inline ostream& operator<<(ostream& out, IllegalInput &ii)
{
	return ii.print(out);
}

#endif /* ILLEGALINPUT_HPP_ */
