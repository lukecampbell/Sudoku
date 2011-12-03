// Board.hpp
// Campbelll, Lucas
// 7 Sep 2011
// Declaration for the Board Class

#ifndef BOARD_HPP__
#define BOARD_HPP__

// INCLUDES AND MACROS //

#include "Sudoku.hpp"
#include "Cluster.hpp"
#include "Square.hpp"
#include "SquareState.hpp"
#include "IllegalInput.hpp"
#include "FatalException.hpp"
#include <sstream>
#include <string>
#include <iostream>
using namespace std;

const int MAX_SQUARES=81;

// END INCLUDES AND MACROS //

// A structure to hold the 81 Square's states
struct Frame
{
    SquareState states[81];
};

//-----------------------------------------------------------------------------
// Board class
// Models the Sudoku Board
class Board
{
protected:
    Square *board[MAX_SQUARES]; // The board
    ifstream board_reader; // reader for data
    Cluster **board_clusters; // the clusters on the board


public:

    static const int MIN_CLUSTERS=27;

    // Default Constructor
    Board(int clusters=MIN_CLUSTERS);
    // Loads the board based on the input
    Board(const char *filename);
    // For debugging purposes only as of yet
    virtual ~Board();
    // Subscript for a square member
    virtual Square& sub(int j, int k);

    // Returns a square at the specified index
    virtual const Square& operator[](int index);
    // Prints the board (square by square)
    ostream& print(ostream& out); // Prints the board
    // Prints the graphical board
    ostream& printGUI(ostream& out);
    // Saves the current board's state to the frame
    void saveState(Frame *);
    // Restores the board's state from the designated frame
    void restoreState(Frame *);
    // Returns a desired cluster
    // for box type the ordering goes left to right
    virtual Cluster* getCluster(ClusterType type, int num);

};
inline ostream& operator<<(ostream& out, Board& b)
{
    return b.print(out);
}

#endif // BOARD_HPP__
