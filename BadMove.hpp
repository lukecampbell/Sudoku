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
protected:
	unsigned short int row;
	unsigned short int col;
	char illegalInput;
	string information;
public:
	BadMove(unsigned short int row=-1,
			unsigned short int col=-1,
			char illegalInput='\0');
	virtual ~BadMove();
	virtual const char *what() const;

	virtual ostream &print(ostream &out); // TODO: make const

	void setRow(unsigned short int row);
	void setCol(unsigned short int col);
	void setValue(char value);
	void setMessage(const string &message);

	unsigned short int getRow() const;
	unsigned short int getCol() const;
	char getValue() const;
	string getMessage() const;

};
inline ostream& operator<<(ostream& out, BadMove& b)
{
	return b.print(out);

}

#endif /* BADMOVE_H_ */
