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
	state_value = square_value;
	state_bitmap = square_value;
	state_count = square_count;
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
	state_bitmap = square_bitmap;
	state_count = square_count;

}

void
SquareState::turnOff(int n)
{
	Square::turnOff(n);
	state_value = square_value;
	state_bitmap = square_value;
	state_count = square_count;

}

ostream&
SquareState::print(ostream &out) const
{
	string possibilities;
	for(int k=1;k<=9;k++)
	{
		unsigned short int bit = (state_bitmap >> k) & 0x01;
		if(bit==0)
			possibilities+=' ';
		else
			possibilities+=k+'0';
	}
	out<<"SquareState: ["<<getRow()<<","<<getCol()<<"]: "
		<<state_value
		<<" Possibilities: ("
		<<state_count<<") "
		<<possibilities;

	return out;
}

void
SquareState::operator=(const Square &copy)
{
	Square::operator=(copy);
	state_value = square_value;
	state_bitmap = square_value;
	state_count = square_count;
}

