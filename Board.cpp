// Board.cpp
// Campbell, Lucas
// 8 Sep 2011
// Implementation for Board Class

#include "Board.hpp"



//-----------------------------------------------------------------------------
// Board()
// Default Cosntructor
Board::Board(bool diagonal)
   :diagonalSudoku(diagonal)
{
    Square *lineup[9]; // the working set to allocate the clusters
    unsigned short int allocs = 0; // how many clusters we allocate
    //------------------------------------------------
    // Handle the case where we can't allocate enough
    // memory for the clusers
    //------------------------------------------------
    try
    {

        //------------------------------------------------
        // Initiate the squares in board
        //------------------------------------------------

        for (int k = 0; k < 9; k++)
            for (int x = 0; x < 9; x++)
                board[9 * k + x] = new Square(k, x);

        // What the above is really doing is this:
        // board[9*k + x].operator=( &Square(k,x))
        // we need to do it this way...

        //------------------------------------------------
        // Allocate the clusters for each row
        //------------------------------------------------
        for (int k = 0; k < 9; k++)
        {

            for (int x = 0; x < 9; x++)
                lineup[x] = board[9 * k + x];
            board_clusters[k] = new Cluster(CLUSTER_ROW, lineup);
            allocs++; // keep track of how many we alloc

        }

        //------------------------------------------------
        // Allocate the clusters for each column
        //------------------------------------------------
        for (int k = 0; k < 9; k++)
        {

            for (int x = 0; x < 9; x++)
                lineup[x] = board[x * 9 + k];
            board_clusters[k + 9] = new Cluster(CLUSTER_COL, lineup);
            allocs++; // keep track of how many we alloc
        }

        //------------------------------------------------
        // Allocate the clusters for each box
        //------------------------------------------------
        for (int k = 0; k < 9; k++)
        {
            for (int x = 0; x < 9; x++)
            { // Create each box using simple modular arithmetic
                int row = (x / 3) + (3 * (k / 3));
                int col = (x % 3) + (3 * (k % 3));
                lineup[x] = board[9 * row + col];
            }
            board_clusters[k + 18] = new Cluster(CLUSTER_BOX, lineup);
            allocs++; // keep track of how many we alloc
        }

        if(diagonalSudoku)
        {
           //------------------------------------------------
           // Allocate the clusters for the diagonals
           //------------------------------------------------
           // upper left to lower right (increment)
           for(int k=0;k<9;k++)
           {
               lineup[k] = board[9 * k + k];

           }
           board_clusters[27] = new Cluster(CLUSTER_DIAGONAL, lineup);
           allocs++;


           //------------------------------------------------
           // Allocate the clusters for the diagonals
           //------------------------------------------------
           // upper right to lower left
           for(int k=0;k<9;k++)
           {
               lineup[k] = board[9*k + (8-k)];
           }
           board_clusters[28] = new Cluster(CLUSTER_DIAGONAL, lineup);
           allocs++;
        }
    }
    //------------------------------------------------
    // Handle a failed alloc
    //------------------------------------------------
    catch (bad_alloc& ba)
    {
        // free the allocated clusters so far.
        unsigned short int k = 0;
        for (k = 0; k < allocs; k++)
            delete board_clusters[k];

        throw FatalException("Board::Board() failed to allocate memory for clusters.\n");
    }
}

//-----------------------------------------------------------------------------
// Board()
// Constructor that initializes the ifstream
// const char *filename - The path to the file
Board::Board(const char *filename)
   :diagonalSudoku(false)
{

    //------------------------------------------------
    // Handle file input
    //------------------------------------------------
    board_reader.open(filename, ifstream::in);
    if (board_reader.fail())
    { // TODO add a test to the test plan to test the filename
        throw FatalException("Failed to read input file");
    }

    Square *lineup[9]; // the working set to allocate the clusters
    unsigned short int allocs = 0; // how many clusters we allocate
    //------------------------------------------------
    // Handle the case where we can't allocate enough
    // memory for the clusers
    //------------------------------------------------
    try
    {

        //------------------------------------------------
        // Initiate the squares in board
        //------------------------------------------------

        for (int k = 0; k < 9; k++)
            for (int x = 0; x < 9; x++)
                board[9 * k + x] = new Square(k, x);

        // What the above is really doing is this:
        // board[9*k + x].operator=( &Square(k,x))
        // we need to do it this way...

        //------------------------------------------------
        // Allocate the clusters for each row
        //------------------------------------------------
        for (int k = 0; k < 9; k++)
        {

            for (int x = 0; x < 9; x++)
                lineup[x] = board[9 * k + x];
            board_clusters[k] = new Cluster(CLUSTER_ROW, lineup);
            allocs++; // keep track of how many we alloc

        }

        //------------------------------------------------
        // Allocate the clusters for each column
        //------------------------------------------------
        for (int k = 0; k < 9; k++)
        {

            for (int x = 0; x < 9; x++)
                lineup[x] = board[x * 9 + k];
            board_clusters[k + 9] = new Cluster(CLUSTER_COL, lineup);
            allocs++; // keep track of how many we alloc
        }

        //------------------------------------------------
        // Allocate the clusters for each box
        //------------------------------------------------
        for (int k = 0; k < 9; k++)
        {
            for (int x = 0; x < 9; x++)
            { // Create each box using simple modular arithmetic
                int row = (x / 3) + (3 * (k / 3));
                int col = (x % 3) + (3 * (k % 3));
                lineup[x] = board[9 * row + col];
            }
            board_clusters[k + 18] = new Cluster(CLUSTER_BOX, lineup);
            allocs++; // keep track of how many we alloc
        }
    }
    //------------------------------------------------
    // Handle a failed alloc
    //------------------------------------------------
    catch (bad_alloc& ba)
    {
        // free the allocated clusters so far.
        unsigned short int k = 0;
        for (k = 0; k < allocs; k++)
            delete board_clusters[k];

        throw FatalException("Board::Board() failed to allocate memory for clusters.\n");
    }
}

//-----------------------------------------------------------------------------
// ~Board()
// Destructor that traces the destruction of the Board object
// no return
Board::~Board()
{
    //------------------------------------------------
    // free each of the allocated Cluster objects
    //------------------------------------------------
    for (int k = 0; k < 27; k++)
        delete board_clusters[k];
    for (int k = 0; k < 81; k++)
        delete board[k];
    // below is commented out for flow reasons
    //cout << "Board is destroyed" << endl;

#ifdef __DEBUG__
    DEBUG_CALL(Board::~Board(),__LINE__);
#endif //__DEBUG__
}

//-----------------------------------------------------------------------------
// sub()
// A function to retrieve a Square member in the active Board object
// int j,k - Retrieve a Square object at the subscript [j,k]
// Square& - The Square object referenced from the Board object
Square& Board::sub(int j, int k)
{ 
    if (j < 0 || j > 8)
    {
        stringstream errormsg;
        errormsg<<"The subscript index is out of bounds ["
        		<<j<<","
        		<<k<<"] at row"<<j;

        throw IllegalInput(j,k,'-',errormsg.str());
    }
    if (k < 0 || k > 8)
    {
    	stringstream errormsg;
		errormsg<<"The subscript index is out of bounds ["
				<<j<<","
				<<k<<"] at col"<<k;

		throw IllegalInput(j,k,'-',errormsg.str());
    }
    return *board[9 * j + k];
}

//-----------------------------------------------------------------------------
// print()
// A function to display the Board
// ostream& - The ostream object to be printed to
// ostream& - The ostream that has been printed is returned
ostream& Board::print(ostream& out)
{
    //------------------------------------------------
    // Print the squares
    //------------------------------------------------
    for (int j = 0; j < 9; j++)
    {
        for (int k = 0; k < 9; k++)
        {
            out << *board[j * 9 + k] << endl;
        }
        out << endl;
    }
    //------------------------------------------------
    // Print the clusters
    //------------------------------------------------
    for (int k = 0; k < 27; k++)
    {
        out << "----------------------------------------------" << endl
                << "Cluster: " << k << endl << *board_clusters[k]
                << "----------------------------------------------" << endl;
    }
    return out;
}

//-----------------------------------------------------------------------------
// printGUI()
// A function to display the Board
// ostream& - The ostream object to be printed to
// ostream& - The ostream that has been printed is returned
ostream& Board::printGUI(ostream& out)
{
   out<<"    1 2 3   4 5 6   7 8 9"<<endl;
      
   out<<"   _______ _______ _______"<<endl; 
   for(int row=1;row<=9;row++)
   {
      out<<row<<" | ";
      for(int col=1;col<=9;col++)
      {
         if(col%3==0)
            out<<sub(row-1,col-1).getValue()<<" | ";
         else
            out<<sub(row-1,col-1).getValue()<<" ";
      }
      out<<endl;
      if(row%3==0)
         out<<"  |_______|_______|_______|"<<endl;
   }
   return out; 
}

//-----------------------------------------------------------------------------
// saveState()
// Saves the current frame
void Board::saveState(Frame *frame)
{
    for (int k = 0; k < 81; k++)
    {
        frame->states[k] = sub(k / 9, k % 9).getState();
    }
}
//-----------------------------------------------------------------------------
// restoreState()
// sets the current state to frame
void Board::restoreState(Frame *frame)
{
    for (int k = 0; k < 81; k++)
    {
    	try {
    		sub(k / 9, k % 9).forceMark(frame->states[k].getValue());
         if(frame->states[k].isConst())
            sub(k/9,k%9).setConst();
    	} catch (BadMove &b) {
    		cerr<<b<<endl;
    	}
        // note: I have to use mark to link it to the Clusters
        // using setState results in unpredictable behavior
    }
}
//-----------------------------------------------------------------------------
// getCluster()
// returns a cluster given the type and an integer 0-8
Cluster* Board::getCluster(ClusterType type, int num)
{
	int offset = ((int) type) * 9 + num;
	if(num<0 || num>8)
		throw FatalException("Board::getCluster() number is out of bounds");
	
	return board_clusters[offset];
}
