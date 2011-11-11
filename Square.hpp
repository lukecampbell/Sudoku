// Square.hpp
// Lucas Campbell
// 6 Sep 2011
// Square.hpp contians the declaration for the Square class
 
//  BEGIN INCLUDES AND MACROS  //
#ifndef SQUARE_HPP__
#define SQUARE_HPP__

#include <vector>

#include "tools.hpp"
#include "Sudoku.hpp"
#include "Cluster.hpp"

using namespace std;
//  END INCLUDEDS AND MACROS   //

// Note: I don't use #pragma once because it is a MSVC macro and may not compile
// correctly, the solaris and HP-UX C Compiler will not compile #pragma once
// macros.  I learned this recently at work on a development project.

class Cluster;


//-----------------------------------------------------------------------------
// Square identifies a square unit on a sudoku board.  It maintains
// the row, column and value maintained within the square.
class Square 
{
  protected:
    char square_value;                 // Identifies the value inside the square
    short int     square_count;        // Possibility Count
    unsigned short int square_bitmap;  // Bit map for used values


  private:
    vector<Cluster *> square_clusters; // The cluster that the square belongs to
    unsigned int  square_row;          // The current row and column for which this
    unsigned int  square_col;          // square resides
  public:
    Square(int row, int col);   // Initializes the Square with the specified
                                // two values
    Square(const Square &copy); // Copy Constructor
    Square();                   // Default constructor
    virtual ~Square();          // Currently used for debugging


    virtual void mark(char value);      // Store the value in the square
    virtual void turnOff(int n);        // Eliminate a possibility
    virtual void addCluster(Cluster *cluster);  // adds a cluster
    virtual ostream& print(ostream &) const;  // Prints the formatted text to the ostream
    virtual void operator=(const Square& copy);
    virtual char getValue() const;            // Gets the current value of square
    int getRow() const;
    int getCol() const;

};
inline ostream& operator<<(ostream & out, Square &square)
{
    square.print(out);
    return out;
}


#endif // SQUARE_HPP__
