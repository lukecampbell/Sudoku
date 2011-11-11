// SquareState.cpp
// Luke Campbell
// 10 Nov 11
// SquareState.cpp contains the definition for the SquareState class

#include "SquareState.hpp"
//-----------------------------------------------------------------------------
// doNothing()
// static function that performs no action, used as a place holder for callbacks
static void doNothing(void *)
{
    return;
}

//-----------------------------------------------------------------------------
// SquareState()
//
SquareState::SquareState()
{
    state_value = '-';
    state_bitmap = 0x3FE;
    state_count = 9;
    registerCallback(&doNothing);
}

//-----------------------------------------------------------------------------
// SquareState(const Square &copy)
//
SquareState::SquareState(const SquareState &copy)
{
    state_value = copy.state_value;
    state_bitmap = copy.state_bitmap;
    state_count = copy.state_count;
    registerCallback(&doNothing);
}

//-----------------------------------------------------------------------------
// ~SquareState()
// Destructor
SquareState::~SquareState()
{

}
//-----------------------------------------------------------------------------
// mark()
// Marks a value into the square
bool SquareState::mark(char value)
{
    if (value == '-')
    {
        state_value = '-';
        state_callback(this);
    }
    //------------------------------------------------
    // Check to see if we are allowed to set it
    //------------------------------------------------
    else if (value >= '1' && value <= '9')
    {
        unsigned short int mask = 0x01 << (value - '0');
        if ((state_bitmap & mask) == 0)
        {
            cerr << *this << endl << "Cannot set to " << value
                    << ": Illegal mark" << endl;
            return false;
        }
        state_value = value;
        state_callback(this);

    } else
    {
        cerr << " Attempted to set an illegal value";
        return false;
    }
    // TODO: Throw an exception for illegal mark


    return true;

}
//-----------------------------------------------------------------------------
// turnOff()
// Removes a possibility from the list of possiblities for this square
void SquareState::turnOff(int n)
{
    unsigned short int mask;
    //------------------------------------------------
    // Check bounds
    //------------------------------------------------
    if (n < 1 || n > 9) // TODO throw exception
        return; // the value is not acceptable
    mask = 0x01 << n;
    if ((mask & state_bitmap) != 0)
    {
        state_bitmap = state_bitmap & ~mask;

        if (state_count > 0)
            state_count--;
    }

}
//-----------------------------------------------------------------------------
// possibilitiesString()
// Returns a string of the remaining possibilities for this square
string SquareState::possibilitiesString() const
{
    string possibilities;
    for (int k = 1; k <= 9; k++)
    {
        unsigned short int bit = (state_bitmap >> k) & 0x01;
        if (bit == 0)
            possibilities += ' ';
        else
            possibilities += k + '0';
    }
    return possibilities;
}
//-----------------------------------------------------------------------------
// print()
// Prints the state of this square
ostream& SquareState::print(ostream &out) const
{
    out << "SquareState: " << state_value << " (" << state_count << ")"
            << possibilitiesString() << endl;

    return out;
}
//-----------------------------------------------------------------------------
// operator=()
// Copies the state of (copy) into this square
void SquareState::operator=(const SquareState &copy)
{
    state_value = copy.state_value;
    state_bitmap = copy.state_bitmap;
    state_count = copy.state_count;
}
//-----------------------------------------------------------------------------
// getValue()
// Returns the current character value of this square
char SquareState::getValue() const
{
    return state_value;
}
//-----------------------------------------------------------------------------
// getCount()
// Returns the remaining possibilities for this square
int SquareState::getCount() const
{
    return state_count;
}
//-----------------------------------------------------------------------------
// registerCallback()
// Registers an event handler for when this square's state changes
void SquareState::registerCallback(eventHandler callback)
{
    state_callback = callback;
}
