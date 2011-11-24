/*
 * BadMove.h
 *
 *  Created on: Nov 24, 2011
 *      Author: luke
 */

#ifndef BADMOVE_H_
#define BADMOVE_H_

#include <exception>
using namespace std;

class BadMove
{
public:
	BadMove();
	virtual ~BadMove();
	virtual const char *what();

};

#endif /* BADMOVE_H_ */
