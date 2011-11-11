// SquareState.hpp
// Luke Campbell
// 10 Nov 11
// SquareState.hpp contains the declaration for the SquareState class


#ifndef SQUARESTATE_HPP_
#define SQUARESTATE_HPP_

#include "Square.hpp"


class SquareState : public Square
{
  protected:
	char               state_value;
	short int          state_count;
	unsigned short int state_bitmap;

  public:
	SquareState();
	SquareState(const Square &copy);
	SquareState(int row, int col);

	virtual ~SquareState();

	void mark(char value);
	void turnOff(int n);
	virtual ostream& print(ostream &) const;
	virtual void operator=(const Square& copy);

};


#endif /* SQUARESTATE_HPP_ */
