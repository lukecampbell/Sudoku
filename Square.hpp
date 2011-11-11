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
  private:
    char square_value;                 // Identifies the value inside the square
    unsigned int  square_row;          // The current row and column for which this
    unsigned int  square_col;          // square resides
    short int     square_count;        // Possibility Count
    unsigned short int square_bitmap;  // Bit map for used values
    vector<Cluster *> square_clusters; // The cluster that the square belongs to

  public:
    Square(int row, int col);   // Initializes the Square with the specified
                                // two values
    Square(const Square &copy); // Copy Constructor
    Square();                   // Default constructor
    ~Square();          // Currently used for debugging


    void mark(char value);      // Store the value in the square
    void turnOff(int n);        // Eliminate a possibility
    void addCluster(Cluster *cluster);  // adds a cluster
    ostream& print(ostream &);  // Prints the formatted text to the ostream
    void operator=(const Square& copy);
    char getValue();            // Gets the current value of square

};
inline ostream& operator<<(ostream & out, Square &square)
{
    square.print(out);
    return out;
}


#endif // SQUARE_HPP__
