// Square.cpp
// Lucas Campbell
// 6 Sep 2011
// Square.cpp provides the implementation for the Square class


//   INCLUDES AND MACROS   //
#include "Square.hpp"

static void
doNothing(void *)
{
	return;
}

//   END INCLUDES AND MACROS  //

//-----------------------------------------------------------------------------
// Square()
// Constructor that only has debugging purposes as of yet
Square::Square(int row, int col)
{
    square_row = row;
    square_col = col;
    square_value = '-';
    square_bitmap=0x3FE;
    square_count=9;
    onChange = &doNothing;
}

//-----------------------------------------------------------------------------
// Square()
// Default constructor
Square::Square()
{
    square_row = 0;
    square_col = 0;
    square_value = '-';
    square_bitmap=0x3FE;
    square_count=9;
    onChange = &doNothing;
}
//-----------------------------------------------------------------------------
// Square()
// Copy Constructor
Square::Square(const Square& copy)
{
	square_value = copy.square_value;
	square_row = copy.square_row;
	square_col = copy.square_col;
	square_count = copy.square_count;
	square_bitmap = copy.square_bitmap;
	square_clusters = copy.square_clusters; // deep copy
	onChange = &doNothing;
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
ostream& Square::print(ostream& out) const
{
    string possibilities;
    // Traverse the bitmap for possibilities make a string
    for(int k=1;k<=9;k++)
    {
        unsigned short int bit = (square_bitmap >> k) & 0x01;    // Determine if the
                 //bit in the kth position is true (available) or
                 //false (unavailable)
        if(bit==0)
            possibilities+=' '; // it's false so it's a space i.e. unavailable
        else
            possibilities+=k+'0'; // it's true so it's the value is available

    }
    out<<"Square ["<<square_row<<","<<square_col<<"]: "
            <<square_value
            <<" Possibilities: ("
            <<square_count<<") "
            <<possibilities;
    return out;
}
//-----------------------------------------------------------------------------
// mark()
// Store a value in the Square
// char value - the character to be in the square
// no return
void Square::mark(char value)
{
    if(value=='-')
    {
        square_value='-';
        onChange(this);
    }
    //------------------------------------------------
    // Check to see if we are allowed to set it
    //------------------------------------------------
    else if(value>='1' && value<='9')
    {
    	unsigned short int mask = 0x01 << (value - '0');
    	if( (square_bitmap & mask) == 0)
    	{
    		cerr<<*this<<endl
    		    <<"Cannot set to "<<value<<": Illegal mark"<<endl;
    		return;
    	}
    	square_value = value;
    	onChange(this);
    	//------------------------------------------------
    	// Shoop it!
    	//------------------------------------------------
    	vector<Cluster *>::iterator it;
    	for(it = square_clusters.begin();it<square_clusters.end();it++)
    			(*it)->shoop(this,value);
    }
    else
    		cerr<<" Attempted to set an illegal value";
    	// TODO: Throw an exception for illegal mark


    return;
}
//-----------------------------------------------------------------------------
// turnOff()
// Eliminate a possibility for the square
// int n - The value of the determinant to be eliminated
// no returns
void Square::turnOff(int n)
{
    unsigned short int mask;
    //------------------------------------------------
    // Check bounds
    //------------------------------------------------
    if(n<1 || n>9)  // TODO throw exception
        return; // the value is not acceptable
    mask = 0x01<<n;
    if((mask & square_bitmap)!=0)
    {
    	square_bitmap = square_bitmap & ~mask;

    	if(square_count>0)
    		square_count--;
    }
}

//-----------------------------------------------------------------------------
// addCluster()
// adds a cluster to the list of clusters that the square belongs to
// Cluster *cluster - The cluster to be added to the vector of clusters
// no return
void Square::addCluster(Cluster *cluster)
{
    if(!cluster)
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
	square_value = copy.square_value;
	square_row = copy.square_row;
	square_col = copy.square_col;
	square_count = copy.square_count;
	square_bitmap = copy.square_bitmap;
	square_clusters = copy.square_clusters; // deep copy

}

//-----------------------------------------------------------------------------
// getValue()
// Returns the value of Square
char Square::getValue() const
{
	return square_value;
}
//-----------------------------------------------------------------------------
// getRow()
// Returns the row of the current square
int
Square::getRow() const
{
	return square_row;
}
//-----------------------------------------------------------------------------
// getCol()
// Returns the column of the current square
int
Square::getCol() const
{
	return square_col;
}
//-----------------------------------------------------------------------------
// registerCallback()
// registers a callback for a change in the square's value
void
Square::registerCallback(eventHandler handler)
{
	onChange = handler;
}
