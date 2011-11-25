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
    testCluster();
    bye();
    return 0;
}


void debugging()
{
   cout<<"    1 2 3   4 5 6   7 8 9"<<endl;
      
   cout<<"   _______ _______ _______"<<endl; 
   for(int k=1;k<=9;k++)
   {
      cout<<k<<" | ";
      for(int i=1;i<=9;i++)
      {
         if(i%3==0)
            cout<<i<<" | ";
         else
            cout<<i<<" ";
      }
      cout<<endl;
      if(k%3==0)
         cout<<"  |_______|_______|_______|"<<endl;
   }
   return;

}



