/*
 * BadMove.h
 *
 *  Created on: Nov 24, 2011
 *      Author: luke
 */

#ifndef BADMOVE_H_
#define BADMOVE_H_

#include <exception>
#include <iostream>
using namespace std;

class BadMove
{
private:
	unsigned short int row;
	unsigned short int col;
	char illegalInput;
public:
	BadMove(int row=-1, int col=-1, char illegalInput='\0');
	virtual ~BadMove();
	virtual const char *what();

	virtual ostream &print(ostream &out);

	void setRow(int row);
	void setCol(int col);
	void setValue(char value);

};

#endif /* BADMOVE_H_ */
