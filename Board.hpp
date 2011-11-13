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
private:
    Square *board[81]; // The board
    ifstream board_reader; // reader for data
    Cluster *board_clusters[27]; // the clusters on the board


public:
    // Default Constructor
    Board();
    // Loads the board based on the input
    Board(const char *filename);
    // For debugging purposes only as of yet
    ~Board();
    // Subscript for a square member
    Square& sub(int j, int k);
    // Prints the board (square by square)
    ostream& print(ostream& out); // Prints the board
    // Prints the graphical board
    ostream& printGUI(ostream& out);
    // Saves the current board's state to the frame
    void saveState(Frame *);
    // Restores the board's state from the designated frame
    void restoreState(Frame *);


};
inline ostream& operator<<(ostream& out, Board& b)
{
    return b.print(out);
}

#endif // BOARD_HPP__
