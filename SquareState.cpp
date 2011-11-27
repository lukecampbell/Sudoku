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
    stateValue = '-';
    stateBitmap = 0x3FE;
    stateCount = 9;
    constFlag = false;
    registerCallback(&doNothing);
}

//-----------------------------------------------------------------------------
// SquareState(const Square &copy)
//
SquareState::SquareState(const SquareState &copy)
{
    stateValue = copy.stateValue;
    stateBitmap = copy.stateBitmap;
    stateCount = copy.stateCount;
    constFlag = copy.constFlag;
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
    //------------------------------------------------
    // check to make sure that the square is not const
    //------------------------------------------------
    if(constFlag)
       throw ConflictingValue(0,0,value,
             "SquareState::mark() attempted to mark a const square");
    if (value == '-' || value == '0' || value==' ')
    {
        if(stateValue!='-')
           turnOn(stateValue-'0');
        stateValue = '-';
        stateCallback(this);
        
        return true; //non value
    }
    //------------------------------------------------
    // Check to see if we are allowed to set it
    //------------------------------------------------
    else if (value >= '1' && value <= '9')
    {
        unsigned short int mask = 0x01 << (value - '0');
        if ((stateBitmap & mask) == 0)
        {

            throw IllegalValue(0,0,value,
            		"SquareState::mark() Attempted to set an illegal value.");
        }
        if(stateValue != '-')
            turnOn(stateValue-'0');
        stateValue = value;
        stateCallback(this);

    } else
    {
        throw IllegalValue(0,0,value,
        		"SquareState::mark() attempted to set an illegal value");
    }

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
    if (n < 1 || n > 9)
        throw FatalException(
         "SquareState::turnOff() attempted to turn off an invalid input");
    mask = 0x01 << n;
    if ((mask & stateBitmap) != 0)
    {
        stateBitmap = stateBitmap & ~mask;

        if (stateCount > 0)
            stateCount--;
    }

}
void SquareState::turnOn(int n)
{
    unsigned short int mask;
    if(n<1 || n>9)
        return;
    mask = 0x01 <<n;
    stateBitmap = stateBitmap | mask;
    if(stateCount<9)
        stateCount++;
}


//-----------------------------------------------------------------------------
// possibilitiesString()
// Returns a string of the remaining possibilities for this square
string SquareState::possibilitiesString() const
{
    string possibilities;
    for (int k = 1; k <= 9; k++)
    {
        unsigned short int bit = (stateBitmap >> k) & 0x01;
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
    out << "SquareState: " << stateValue << " (" << stateCount << ")"
            << possibilitiesString() << endl;

    return out;
}
//-----------------------------------------------------------------------------
// operator=()
// Copies the state of (copy) into this square
void SquareState::operator=(const SquareState &copy)
{
    stateValue = copy.stateValue;
    stateBitmap = copy.stateBitmap;
    stateCount = copy.stateCount;
}
//-----------------------------------------------------------------------------
// getValue()
// Returns the current character value of this square
char SquareState::getValue() const
{
    return stateValue;
}
//-----------------------------------------------------------------------------
// getCount()
// Returns the remaining possibilities for this square
int SquareState::getCount() const
{
    return stateCount;
}
//-----------------------------------------------------------------------------
// isValidInput()
// Returns true if the input is between 1 and 9 and/or is a valid
// empty square value
bool SquareState::isValidInput(char value)
{
	if(value=='-' || value=='0' || value ==' ')
		return true;
	if(value>='1' && value<='9')
		return true;
	return false;
}
//-----------------------------------------------------------------------------
// isPossible()
// Returns true if the value is possible in this SquareState
bool SquareState::isPossible(char value) const
{
	unsigned short int mask=0;
	if(value<'1' || value>'9')
	{
		throw IllegalInput(-1,-1,value,
				"called isPossible with improper integer value");
	}
	mask = value - '0';
	mask = 0x01 << mask;
	if((stateBitmap & mask) != 0)
		return true;
	return false;
}


//-----------------------------------------------------------------------------
// forceMark()
// forces a mark regardless of const
void SquareState::forceMark(char value)
{
   constFlag=false;
   mark(value);
}

//-----------------------------------------------------------------------------
// registerCallback()
// Registers an event handler for when this square's state changes
void SquareState::registerCallback(eventHandler callback)
{
    stateCallback = callback;
}
