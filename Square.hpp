// Square.hpp
// Lucas Campbell
// 6 Sep 2011
// Square.hpp contians the declaration for the Square class

//  BEGIN INCLUDES AND MACROS  //
#ifndef SQUARE_HPP__
#define SQUARE_HPP__

#include <vector>
#include <sstream>

#include "tools.hpp"
#include "Sudoku.hpp"
#include "Cluster.hpp"
#include "SquareState.hpp"
#include "IllegalInput.hpp"
#include "ConflictingValue.hpp"
#include "BadMove.hpp"

using namespace std;
//  END INCLUDEDS AND MACROS   //

// Note: I don't use #pragma once because it is a MSVC macro and may not compile
// correctly, the solaris and HP-UX C Compiler will not compile #pragma once
// macros.  I learned this recently at work on a development project.

class Cluster;




//-----------------------------------------------------------------------------
// Square identifies a square unit on a sudoku board.  It maintains
// the row, column and value maintained within the square.
class Square: public SquareState
{

private:
    vector<Cluster *> squareClusters; // The cluster that the square belongs to
    unsigned int squareRow; // The current row and column for which
    // this
    unsigned int squareCol; // square resides

public:
    Square(int row, int col); // Initializes the Square with the specified
    // two values
    Square(const Square &copy); // Copy Constructor
    Square(); // Default constructor
    virtual ~Square(); // Currently used for debugging


    virtual bool mark(char value); // Store the value in the square

    virtual void addCluster(Cluster *cluster); // adds a cluster
    virtual ostream& print(ostream &) const; // Prints the formatted text to
    // the ostream
    virtual void operator=(const Square& copy);

    int getRow() const; // returns the row of this Square
    int getCol() const; // returns the column of this Square

    const SquareState& getState() const; // returns the current state of this square
    void setState(SquareState &state); // sets the state of this square

    // returns true if any clusters this square is attached to
    // is currently referencing this possibility
    // possibilities are 1-9
    bool isReferenced(int n);
};
inline ostream& operator<<(ostream & out, Square &square)
{
    square.print(out);
    return out;
}

#endif // SQUARE_HPP__
