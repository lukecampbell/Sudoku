// SquareState.cpp
// Luke Campbell
// 10 Nov 11
// SquareState.cpp contains the definition for the SquareState class

#include "SquareState.hpp"

//-----------------------------------------------------------------------------
// SquareState()
//
SquareState::SquareState()
:Square()
{
	state_value = '-';
	state_bitmap=0x3FE;
	state_count = 9;
}

//-----------------------------------------------------------------------------
// SquareState(const Square &copy)
//
SquareState::SquareState(const Square &copy)
:Square(copy)
{
	state_value = copy.square_value;
	state_bitmap = copy.square_bitmap;
	state_count = copy.square_count;
}


SquareState::SquareState(int row, int col)
:Square(row,col)
{
	state_value ='-';
	state_bitmap = 0x3FE;
	state_count = 9;
}

SquareState::~SquareState()
{

}

void
SquareState::mark(char value)
{
	Square::mark(value);
	state_value = square_value;

}

void
SquareState::turnOff(int n)
{

}

ostream&
SquareState::print(ostream &out) const
{
	return out;
}

void
SquareState::operator=(const Square &copy)
{

}

void
SquareState::operator=(const SquareState& copy)
{

}
