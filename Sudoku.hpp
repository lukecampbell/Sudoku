// Sudoku.hpp
// Lucas Campbell
// 8 Sep 2011
// Contains global declarations and macros for Sudoku

#ifndef _SUDOKU_HPP_
#define _SUDOKU_HPP_
// Note I used #ifndef and #def for compatability with C and
// older compilers

// MACROS
#ifdef __DEBUG__
#define DEBUG_CALL(x,line) std::cerr<<#x ": "<<line<<" was called"<<std::endl
#define DEBUG_MSG(x) std::cerr<<x<<std::endl
#endif // __DEBUG__
// END MACROS



//-----------------------------------------------------------------------------
// DECLARATIONS
void testSquare();  // Test the Square class
void testBoard();   // Test the Board class
void testCluster(); // Test clusters
void testTogether();  // Test putting everything together
void debugging();   // Debugging environment for general debugging

// END DECLARATIONS



#endif // _SUDOKU_HPP_
