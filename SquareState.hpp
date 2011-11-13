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

typedef void (*eventHandler)(void *);

class SquareState
{
protected:
    char state_value;
    short int state_count;
    unsigned short int state_bitmap;
    eventHandler state_callback;

public:
    SquareState();
    SquareState(const SquareState &copy);

    virtual ~SquareState();

    virtual bool mark(char value);
    virtual void turnOff(int n);
    virtual void turnOn(int n);
    string possibilitiesString() const; // A string of the possibilities
    virtual ostream& print(ostream &) const;
    virtual void operator=(const SquareState& copy);
    virtual void registerCallback(eventHandler); // Registers a callback
    // for the onChange callback
    char getValue() const;
    int getCount() const;

};
inline ostream& operator<<(ostream &out, SquareState &state)
{
    return state.print(out);
}

#endif /* SQUARESTATE_HPP_ */
