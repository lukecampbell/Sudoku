// SquareState.hpp
// Luke Campbell
// 10 Nov 11
// SquareState.hpp contains the declaration for the SquareState class


#ifndef SQUARESTATE_HPP_
#define SQUARESTATE_HPP_

#include "Sudoku.hpp"
#include <iostream>
#include <string>
using namespace std;

// Not used in this project see registerCallback below
typedef void (*eventHandler)(void *);


// Models the state and possibilities of a Square in Sudoku
// Maintains a bitmap of possibilities for the remaining numbers that could be
// assigned to this square.  Also maintains a current value for the square and
// the number of possibilities remaining.
class SquareState
{
protected:
    char state_value;
    short int state_count;
    unsigned short int state_bitmap;
    eventHandler state_callback;

public:
    // Initializes a generic square state
    // All possibilities are on and the current value is '-' which is a
    // null state
    SquareState();

    // Copy constructor that copies the state from the paramter
    // to this square
    SquareState(const SquareState &copy);

    // Destructor
    virtual ~SquareState();

    // Marks the specified value
    virtual bool mark(char value);

    // Eliminates a possibility from the square state
    virtual void turnOff(int n);

    // Enables a possibility in the Square's state
    virtual void turnOn(int n);

    // Returns the string containing the possibilities
    // this is used in conjuction with sudokumm
    // the graphical interface to this project
    string possibilitiesString() const;

    // Prints the current square's state
    // the value followed by the possibilities
    virtual ostream& print(ostream &) const;

    // Mimics the copy constructor's actions but on ths overloaded operator
    virtual void operator=(const SquareState& copy);

    // This is used in conjunction with the sudokumm project
    // It will be eventually implemented as an event handler
    // for when the state of the square is changed
    virtual void registerCallback(eventHandler); // Registers a callback

    // Returns the current character value of the square
    char getValue() const;

    // Returns the number of possibilities remaining
    int getCount() const;

};
inline ostream& operator<<(ostream &out, SquareState &state)
{
    return state.print(out);
}

#endif /* SQUARESTATE_HPP_ */
