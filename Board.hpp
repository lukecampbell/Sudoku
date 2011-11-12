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
// END INCLUDES AND MACROS //


struct Frame
{
    SquareState states[81];
};

//-----------------------------------------------------------------------------
// Board class
// Models the Sudoku Board
class Board
{
private:
    Square *board[81]; // The board
    ifstream board_reader; // reader for data
    Cluster *board_clusters[27]; // the clusters on the board


public:
    Board(); // Default Constructor
    Board(const char *filename); // Initializes
    ~Board(); // For debugging purposes only as of yet
    Square& sub(int j, int k); // Subscript for a Square member

    ostream& print(ostream& out); // Prints the board

    ostream& printGUI(ostream& out); // Prints formatted GUI board

    void saveState(Frame *);
    void restoreState(Frame *);


};
inline ostream& operator<<(ostream& out, Board& b)
{
    return b.print(out);
}

#endif // BOARD_HPP__
