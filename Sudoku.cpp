// Sudoku.cpp
// Lucas Campbell
// 6 Sep 2011
// Sudoku.cpp contains the main program


//-----------------------------------------------------------------------------
//   INCLUDES AND MACROS  //
#include "Sudoku.hpp"
#include "Board.hpp"
#include "SquareState.hpp"
#include "BadMove.hpp"
#include "Game.hpp"

#include <sys/types.h>
#include <regex.h>
#include <stdio.h>
//  END INCLUDES AND MACROS //

inline void runTests()
{
    testSquare();
    testBoard();
    testCluster();
    testBadMoveException();
    testIllegalInputException();
    testConflictingValueException();
    testFatalException();
	testGetCluster();
}

static void gameInit()
{
   Game newGame;
   try {
      newGame.run();
   } catch(BadMove &b) {
      cout<<b<<endl;
   } catch(FatalException &f) {
      char errormsg[] = "%s\n";
      fatal(errormsg,f.what());
   }
}

//-----------------------------------------------------------------------------
// main()
// arguments from command line argc and argv
// returns 0 regardless of execution
int main(int argc, char *argv[])
{
    if(argc>1)
    {
       cout<<argv[1]<<endl;
       if(!strcmp(argv[1],"test") || !strcmp(argv[1],"--test"))
       {
          banner();
          runTests();
          bye();
       }
       return 0;
    }

    banner();
    gameInit();
    bye();
    return 0;
}


void debugging()
{
	Board board;
	board.sub(0,0).mark('2');
	for(int i=0;i<9;i++)
		cout<<board.sub(0,i).isReferenced(1)<<endl;

}



