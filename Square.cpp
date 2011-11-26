// Square.cpp
// Lucas Campbell
// 6 Sep 2011
// Square.cpp provides the implementation for the Square class


//   INCLUDES AND MACROS   //
#include "Square.hpp"

//   END INCLUDES AND MACROS  //

//-----------------------------------------------------------------------------
// Square()
// Constructor that only has debugging purposes as of yet
Square::Square(int row, int col) :
    SquareState()
{
    squareRow = row;
    squareCol = col;
}

//-----------------------------------------------------------------------------
// Square()
// Default constructor
Square::Square() :
    SquareState()
{
    squareRow = 0;
    squareCol = 0;

}
//-----------------------------------------------------------------------------
// Square()
// Copy Constructor
Square::Square(const Square& copy) :
    SquareState(copy)
{
    squareRow = copy.squareRow;
    squareCol = copy.squareCol;
    squareClusters = copy.squareClusters; // deep copy
}

//-----------------------------------------------------------------------------
// ~Square()
// Destructor is only defined for debugging purposes as of yet
Square::~Square()
{
#ifdef __DEBUG__
    //DEBUG_CALL(Square::~Square(),__LINE__);
#endif // __DEBUG__
    //TODO I strongly recommend leaving this to the debuugging only
    //cout<<"Deleting "<<(*this)<<endl;
}
//-----------------------------------------------------------------------------
// print()
// out - an ostream& for the desired output stream
// returns a reference to an ostream with the formatted text
ostream&
Square::print(ostream& out) const
{

    out << "Square [" << squareRow + 1 << "," << squareCol + 1 << "]: "
            << stateValue << " Possibilities: (" << stateCount << ") "
            << possibilitiesString();
    return out;
}
//-----------------------------------------------------------------------------
// mark()
// Store a value in the Square
// char value - the character to be in the square
// no return
bool Square::mark(char value)
{
    char val = stateValue;

    //------------------------------------------------
    // if it's a const throw a conflicting val exception
    //------------------------------------------------
    if(constFlag)
       throw ConflictingValue(squareRow,squareCol,value,
             "Square::mark() attempted to mark a constant square");
    // Exceptions testing
    if(!isValidInput(value))
    {
    	throw IllegalInput(squareRow,squareCol,value,"invalid input");
    }
    if(value>='1' && value<='9')
		if(!isPossible(value))
		{
			stringstream message;
			message<<"The value is not a value that is possible for "
					<<"this square."<<endl;
			message<<*this<<endl;

			throw ConflictingValue(squareRow, squareCol, value,
					message.str());
		}
    bool ret = SquareState::mark(value);
    //------------------------------------------------
    // Unshoop old value
    //------------------------------------------------
    if(ret && (val!='-'))
    {

        vector<Cluster *>::iterator it;
        for(it = squareClusters.begin();it<squareClusters.end();it++)
        {
            (*it)->unshoop(this,val);
        }
    }
    //------------------------------------------------
    // Shoop it!
    //------------------------------------------------
    if (ret)
    {
        vector<Cluster *>::iterator it;
        for (it = squareClusters.begin(); it < squareClusters.end(); it++)
            (*it)->shoop(this, value);
    }
    return ret;
}

//-----------------------------------------------------------------------------
// addCluster()
// adds a cluster to the list of clusters that the square belongs to
// Cluster *cluster - The cluster to be added to the vector of clusters
// no return
void Square::addCluster(Cluster *cluster)
{
    if (!cluster)
    {
        throw FatalException("Square::addCluster() null pointer");
    }
    squareClusters.push_back(cluster);
}

//-----------------------------------------------------------------------------
// operator=()
// Copy Constructor
void Square::operator =(const Square& copy)
{
    SquareState::operator=(copy);
    squareRow = copy.squareRow;
    squareCol = copy.squareCol;

    squareClusters = copy.squareClusters; // deep copy

}

//-----------------------------------------------------------------------------
// getRow()
// Returns the row of the current square
int Square::getRow() const
{
    return squareRow;
}
//-----------------------------------------------------------------------------
// getCol()
// Returns the column of the current square
int Square::getCol() const
{
    return squareCol;
}

//-----------------------------------------------------------------------------
// getState()
// Returns the current state of this square
SquareState Square::getState() const
{
    return *this;
}

//-----------------------------------------------------------------------------
// setState()
// assigns a state to this square
void Square::setState(SquareState &state)
{
    SquareState::operator=(state);
}

bool Square::isReferenced(int n)
{
	vector<Cluster *>::iterator it;
	for(it=squareClusters.begin();it!=squareClusters.end();it++)
		if((*it)->isReferenced(n))
			return true;
	return false;
}
