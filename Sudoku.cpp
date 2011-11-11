// Sudoku.cpp
// Lucas Campbell
// 6 Sep 2011
// Sudoku.cpp contains the main program


//-----------------------------------------------------------------------------
//   INCLUDES AND MACROS  //
#include "Sudoku.hpp"
#include "Board.hpp"
#include "SquareState.hpp"

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

void callback(void *arg)
{
	cout<<"callback called"<<endl;
}


void debugging()
{
   Board board;
   board.printGUI(cout);
   SquareState test;
   test.mark('1');
   board.sub(2,2).setState(test);
   board.printGUI(cout);
}

//-----------------------------------------------------------------------------
// debugging()
// General debugging environment()
void boardInterface()
{
#ifdef __DEBUG__
    DEBUG_CALL(debugging(),__LINE__);
#endif //__DEBUG__
    char game[] = {
    		0,0,0,2,6,0,7,0,1,
    		6,8,0,0,7,0,0,9,0,
    		1,9,0,0,0,4,5,0,0,
    		8,2,0,1,0,0,0,4,0,
    		0,0,4,6,0,2,9,0,0,
    		0,5,0,0,0,3,0,2,8,
    		0,0,9,3,0,0,0,7,4,
    		0,4,0,0,5,0,0,3,6,
    		7,0,3,0,1,8,0,0,0
    };

    int n = sizeof(game)/sizeof(game[0]);
    Board board;
    for(int i=0;i<n;i++)
    {
    	cout<<"("<<i/9<<","<<i%9<<")"<<endl;
    	if(game[i]==0)
    		continue;

    	board.sub(i/9,i%9).mark(game[i]+'0');
    }
    cout<<board<<endl;
    board.printGUI(cout);
    cout<<"I want to put an 8 in the lower right corner"<<endl;
    board.sub(8,8).mark('8');

}


