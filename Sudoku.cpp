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


//-----------------------------------------------------------------------------
// main()
// arguments from command line argc and argv
// returns 0 regardless of execution
int main(int argc, char *argv[])
{
    banner();
    debugging();
    bye();
    return 0;
}


void debugging()
{
	Game newGame;
	try {
		newGame.loadGame("saved.sudoku");

	} catch(BadMove &b)
	{
		cout<<b<<endl;
	}
	newGame.run();
}



