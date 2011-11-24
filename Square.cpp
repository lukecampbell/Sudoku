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
    square_row = row;
    square_col = col;
}

//-----------------------------------------------------------------------------
// Square()
// Default constructor
Square::Square() :
    SquareState()
{
    square_row = 0;
    square_col = 0;

}
//-----------------------------------------------------------------------------
// Square()
// Copy Constructor
Square::Square(const Square& copy) :
    SquareState(copy)
{
    square_row = copy.square_row;
    square_col = copy.square_col;
    square_clusters = copy.square_clusters; // deep copy
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

    out << "Square [" << square_row + 1 << "," << square_col + 1 << "]: "
            << state_value << " Possibilities: (" << state_count << ") "
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
    char val = state_value;

    // Exceptions testing
    if(!isValidInput(value))
    {
    	throw IllegalInput(square_row,square_col,value,"invalid input");
    }
    if(!isPossible(value))
    {
    	throw ConflictingValue(square_row, square_col, value,
    			"the value is not a value that is possible for this square");
    }
    bool ret = SquareState::mark(value);
    //------------------------------------------------
    // Unshoop old value
    //------------------------------------------------
    if(ret && (val!='-'))
    {
        vector<Cluster *>::iterator it;
        for(it = square_clusters.begin();it<square_clusters.end();it++)
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
        for (it = square_clusters.begin(); it < square_clusters.end(); it++)
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
        //TODO: Throw an error here for null pointer
        char errmsg[] = "Null pointer\n";
        fatal(errmsg);
    }
    square_clusters.push_back(cluster);
}

//-----------------------------------------------------------------------------
// operator=()
// Copy Constructor
void Square::operator =(const Square& copy)
{
    SquareState::operator=(copy);
    square_row = copy.square_row;
    square_col = copy.square_col;

    square_clusters = copy.square_clusters; // deep copy

}

//-----------------------------------------------------------------------------
// getRow()
// Returns the row of the current square
int Square::getRow() const
{
    return square_row;
}
//-----------------------------------------------------------------------------
// getCol()
// Returns the column of the current square
int Square::getCol() const
{
    return square_col;
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

