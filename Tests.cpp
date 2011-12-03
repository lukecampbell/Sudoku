// Tests.cpp
// Lucas Campbell
// 1 Oct 2011
// Contains the testing functions

#include <typeinfo>

#include "Sudoku.hpp"
#include "Square.hpp"
#include "Board.hpp"
#include "DiagBoard.hpp"
#include "Cluster.hpp"
#include "Game.hpp"
#include "BadMove.hpp"
#include "IllegalInput.hpp"
#include "ConflictingValue.hpp"
#include "FatalException.hpp"


//-----------------------------------------------------------------------------
// testGetCluster()
// Unit test for getCluster
void testGetCluster()
{
	Board myBoard;
	Cluster *cluster;
	bool passed=true;
	cout<<"getCluster Unit Test"<<endl;
   //------------------------------------------
   // The unit test should succeed if I can 
   // successfully get a cluster from 
   // getCluster()
   //------------------------------------------
	try {
		cout<<" - testing accessor method"<<endl;
		cluster = myBoard.getCluster(CLUSTER_ROW,8);
	} catch(FatalException &fe) {
		cout<<"   test failed.";
		cerr<<"getCluster Unit Test Failed"<<endl
			<<" - cluster failed to be returned by Board::getCluster()"<<endl;
		return;
	}
	cout<<"   test succeeded."<<endl;

   //------------------------------------------
   // it should fail if I try to get a cluster
   // out of bounds (0-8)
   //------------------------------------------
	try {
		cout<<" - testing accessor out of bounds"<<endl;
		cluster = myBoard.getCluster(CLUSTER_ROW,9); // out of bounds
		
	} catch(FatalException &fe) {
		cout<<"   test succeeded."<<endl;
	}
	cout<<" - testing shooping and accuracy"<<endl;
   //------------------------------------------
   // Cluster Box Unit Test
   //------------------------------------------
	cout<<"    - testing row"<<endl;
	myBoard.sub(0,0).mark('1');
	cluster = myBoard.getCluster(CLUSTER_ROW,0);
	for(int k=1;k<9;k++)
	{
		Square *square = cluster->getSquare(k);
		if(square->isPossible('1'))
		{
			
			cout<<"      test failed."<<endl;
			cerr<<"getCluster Test Failed"<<endl
				<<"  - The accuracy of the shoop failed"<<endl;
			passed = false;
		}
	}
	if(passed)
	{
		cout<<"      test succeeded."<<endl;
	}
   else
      passed=true; // reset

   //------------------------------------------
   // Cluster Column Unit Test
   //------------------------------------------
	cout<<"    - testing column"<<endl;
	cluster = myBoard.getCluster(CLUSTER_COL,0);  // get the first column
	for(int k=1;k<9;k++)
	{
		Square *square = cluster->getSquare(k);
		if(square->isPossible('1'))
		{
			
			cout<<"      test failed."<<endl;
			cerr<<"getCluster Test Failed"<<endl
				<<"  - The accuracy of the shoop failed"<<endl;
			passed = false;
		}
	}
	if(passed)
	{
		cout<<"      test succeeded."<<endl;
	}

   //------------------------------------------
   // Cluster Box Unit Test
   //------------------------------------------
	cout<<"    - testing box"<<endl;
	cluster = myBoard.getCluster(CLUSTER_BOX,0);  // get the first box
	for(int k=1;k<9;k++)
	{
		Square *square = cluster->getSquare(k);
		if(square->isPossible('1'))
		{
			
			cout<<"      test failed."<<endl;
			cerr<<"getCluster Test Failed"<<endl
				<<"  - The accuracy of the shoop failed"<<endl;
			passed = false;
		}
	}
	if(passed)
	{
		cout<<"      test succeeded."<<endl;
	}
   //------------------------------------------
   // Cluster Diagonal Unit Test
   //------------------------------------------
   cout<<"    - testing diagonal clustering"<<endl;
   Board *diagonalBoard = new DiagBoard();


   // a diagonal shoop should occur
   diagonalBoard->sub(0,0).mark('1');
   for(int k=1;k<9;k++)
   {
      if(diagonalBoard->sub(k,k).isPossible('1'))
      {
         cout<<"      diagonal cluster test failed."<<endl;
         cerr<<"Diagonal Cluster Test Failed"<<endl
             <<" - The accuracy of the shoop from upper left to lower right diagonal failed"<<endl;
         return;
      }
      
   }
   cout<<"      test succeeded."<<endl;

   cout<<"    - testing diagonal clustering (other)"<<endl;
   // the other diagonal shoop should occur
   diagonalBoard->sub(0,8).mark('2');
   for(int k=1;k<9;k++)
   {
      if(diagonalBoard->sub(k,8-k).isPossible('2'))
      {
         cout<<"      diagonal cluster test failed."<<endl;
         cerr<<"Diagonal Cluster Test Failed"<<endl
             <<" - The accuracy of the shoop from the upper right to the lower left diagonal failed"
             <<endl;
         return;

      }
   }
   cout<<"      test succeeded."<<endl;
   delete diagonalBoard;
}

//-----------------------------------------------------------------------------
// testFatal()
// Unit test for a fatal execution
void testFatal()
{
   cout<<"Fatal Unit Test"<<endl;
   // it should successsfully end program execution
   try {
      cout<<" - Testing Fatal Execution Interruption"<<endl;
      throw FatalException("   test succeeded.");
   } catch(FatalException &f) {
      // Error message format, using char[] because param
      // for fatal() is char* not const char*
      char errormsg[] = "%s\n"; 
      cout<<"   caught..."<<endl;
      fatal(errormsg,f.what());
   }
   cout<<"   test failed."<<endl;
   cerr<<"Fatal Unit Test Failed"<<endl
       <<" - The program failed to terminate with a fatal exception."<<endl;

}


//-----------------------------------------------------------------------------
// testFatalException()
// Unit test for Fatal Exception
void testFatalException()
{
   FatalException fe("Unit Test");
   bool wasThrown=false;
   cout<<"Fatal Exception test"<<endl;
   // it should successfully be thrown and caught
   cout<<" - test throw/catch"<<endl;
   try {
      throw fe;
   } catch(FatalException fe) {
      cout<<"   test successful."<<endl;
      cout<<"(message: "<<fe<<")"<<endl;
   } catch(...) {
      cout<<"   test failed."<<endl;
      cerr<<"Fatal Exception Test Failed"<<endl
          <<"  - Failed to be thrown/caught."<<endl;
   }
   // it should be thrown when a Board is created with a non-existent file
   try {
      cout<<" - test load board without good file"<<endl;
      Board myBoard("does_not_exist");
   } catch(FatalException &f) {
      cout<<"   test successful."<<endl;
      wasThrown=true;
   }
   if(!wasThrown)
   {
      cout<<"   test failed."<<endl;
      cerr<<"Fatal Exception Test Failed"<<endl
          <<"  - Failed to be thrown in Board class for bad file input"<<endl;
   }
   
}

//-----------------------------------------------------------------------------
// testConflictingValueException()
// Unit test for Conflicting Value Exception
void testConflictingValueException()
{
	ConflictingValue bad;
   bool constPass=false;
	cout<<"Conflicting Value Exception test"<<endl;
	// it should successfully be thrown and caught
	cout<<" - testing throw/catch"<<endl;
	try {
		throw bad;
	} catch(BadMove &bm) {
		cout<<"   test successful."<<endl;
	} catch(...) {
		cout<<"   test failed."<<endl;
		cerr<<"Conflicting Value Test Failed"<<endl
			<<"  - Failed to be thrown/caught."<<endl;
	}

	// it should be thrown when we try to mark a square that
	// doesn't have the appropriate value in the list of possibilities
	Square testSquare;
	bool wasThrown = false; // indicates that the exception was thrown
	cout<<" - testing Square::mark()"<<endl;
	testSquare.turnOff(3);
	try {
		testSquare.mark('3');

	} catch(ConflictingValue &cv) {
		cout<<"   test successful."<<endl;
		cout<<cv<<endl;
		wasThrown=true;
	} catch(...) {
		cerr<<"   test failed."<<endl
			<<"   Square class should throw ConflictingValue exception "
			<<"when marked with an impossible value"<<endl;
	}
	if(!wasThrown)
	{
		cout<<"   test failed."<<endl;
		cerr<<"Conflicting Value Test Failed"<<endl
			<<"  - Square class failed to throw an exception for marking"
			<<"    an impossible value"<<endl;
	}
   // a conflicting value exception should be thrown if you try to
   // mark a const square
   cout<<"Const Square Mark Test"<<endl;
   Square constSquare;
   constSquare.mark('1');
   constSquare.setConst();
   try {
      constSquare.mark('2');
   } catch(ConflictingValue &cv) {
      constPass=true;
      cout<<"  - test succeeded"<<endl;
      cout<<cv<<endl;
   } catch(...) {
      cout<<"  - test failed"<<endl;
   }
   if(!constPass)
   {
      cout<<"  - test failed"<<endl;
   }
}
//-----------------------------------------------------------------------------
// testIllegalInputException()
// Unit test for IllegalInput exception
void testIllegalInputException()
{
	IllegalInput bad;

	// Used to make sure that the exception was thrown and caught
	bool wasThrown = false;
	cout<<"Illegal Input Exception test"<<endl;

	// it should successfully be thrown and caught
	cout<<" - testing throw/catch"<<endl;
	try {
		throw bad;

	} catch(BadMove &bm) {
		cout<<"   test successful."<<endl;
	} catch(...) {
		cout<<"   test failed."<<endl;
		cerr<<"Illegal Input Exception"<<endl
		    <<"  - Illegal Input Exception failed to be thrown and caught"
		    <<endl;
	}

	// it should successfully throw an exception when
	// you try to input an illegal value into a square

	Square testSquare;
	cout<<" - testing Illegal Square::mark"<<endl;

	try{
		testSquare.mark('a'); // illegal mark
	} catch(IllegalInput &ii) {
		cout<<" - test successful."<<endl;
		cout<<ii<<endl;
		wasThrown=true;
	}
	if(!wasThrown)
	{
		cout<<" - test failed."<<endl;
				cerr<<"Illegal Input Exception"<<endl
			<<"  - Failed to throw an exception when Square is marked with"
					<<" wrong value"<<endl;
	}


}

//-----------------------------------------------------------------------------
// testBadMoveException()
// Unit test for BadMove exception
void testBadMoveException()
{

	BadMove badMove;

	cout<<"Bad Move Exception"<<endl;
	// test creation and throwing
	cout<<" - testing throw/catch"<<endl;
	try {
		throw badMove;
	} catch(BadMove &bm) {
		cout<<"   test satisfactory"<<endl;
	} catch(...) {
		cout<<"   test failed."<<endl;
		cerr<<"Bad Move Exception Test Failed"<<endl
			<<"  - Failed to be thrown and caught"<<endl;
	}

	cout<<" - testing print()"<<endl;
	if(typeid(cout)==typeid(badMove.print(cout)))
	{
		cout<<"   test succeeded"<<endl;
	}
	else
	{
		cout<<"   test failed"<<endl;
		cerr<<"Bad Move Exception Test Failed"<<endl
			<<"  - Failed to print correctly"<<endl;
	}



}

//-----------------------------------------------------------------------------
// testGameRun()
// This test is the compilation of all tests
// loads a known sudoku puzzle provided with this project
void testGameRun()
{
   Game newGame;
   try {
      newGame.loadGame("saved.sudoku");
      newGame.run();
   } catch(BadMove &b) {
      cout<<b<<endl;
   } catch(FatalException &f) {
      // error message format
      char errormsg[] = "%s\n";
      fatal(errormsg,f.what());
   }
}

//-----------------------------------------------------------------------------
// testSquare()
// Performs an array of tests on the Square class
// no arguments
// no return
void testSquare()
{
    cout << "Begining testing of Square..." << endl;
    cout<<"  - test construction"<<endl;

    Square test;
    // it should successfully be constructed
    cout<<"    test succeeded."<<endl;


    //------------------------------------
    // it should be able to mark a square
    //------------------------------------
    cout<<"  - testing mark"<<endl;
    try {
    	if(! test.mark('1'))
    	{
    		cout<<"    test failed."<<endl;
    		return;
    	}
    } catch (BadMove &bm) {
    	cout<<"    test failed."<<endl;
    	cerr<<bm<<endl;
    	return;
    } catch (FatalException &fe) {
    	cout<<"    test failed."<<endl;
    	cerr<<fe<<endl;
    	return;
    }
    cout<<"    test succeeded."<<endl;

    //-----------------------------------------------
    // it should be able to turn off a possibility
    //-----------------------------------------------

    cout<<"  - testing turnOff"<<endl;
    test.turnOff(9);

    if(test.isPossible('9'))
    {
    	cout<<"    test failed."<<endl;
    	return;
    }
    cout<<"    test succeeded."<<endl;
    //-----------------------------------------------
    // it should be able to turn on a possibility
    //-----------------------------------------------
    cout<<"  - testing turnOn"<<endl;
    test.turnOn(9);
    if(!test.isPossible('9'))
    {
    	cout<<"    test failed."<<endl;
    	return;
    }
    cout<<"    test succeeded."<<endl;


}
//-----------------------------------------------------------------------------
// testBoard()
// Performs an array of tests on the Board class
// no arguments
void testBoard()
{

   Board board;
   cout<<"Testing Board"<<endl;
   // it should generate a Board with the default constructor
   // it should allow a mark in any square within the boards bounds
   cout<<"  - testing construction"<<endl;
   try {
      board.sub(8,8).mark('1');
   } catch (BadMove &b) {
      cout<<"    test failed."<<endl;
      cerr<<"Board Test Failed"<<endl
          <<"    it should allow a mark in any square"<<endl;
      return;
   }
   cout<<"    test succeeded."<<endl;
   
   //------------------------------------
   // test marking
   //------------------------------------

   // it should work with a file in accordance with specs
   Board boardFile("INPUT");
   cout<<"Testing Board with input file: INPUT"<<endl;
   try {
      boardFile.sub(8,8).mark('1');
   } catch( BadMove &b) {
      cout<<"  - test failed."<<endl;
      cerr<<"Board Test Failed"<<endl
          <<"  - it should allow a mark in any square"<<endl;
      return;
   }
   cout<<"  - test succeeded."<<endl;

   //------------------------------------
   // test the [] operator
   //------------------------------------
   
   cout<<"Testing the [] operator with Board"<<endl;
   try {
      boardFile.sub(8,8).mark('1');
   } catch ( BadMove &b) {
      cout<<" - test failed."<<endl;
      cerr<<"Board Test Failed"<<endl
          <<"  - subsequent marking failed"<<endl;
      return;
   }

   if(board[80].getValue()!='1')
   {
      cout<<" - test failed."<<endl;
      cerr<<"Board Test Failed"<<endl
          <<"  - board[] failed to access square"<<endl;
      return;
   }
  
   cout<<"  - test succeeded."<<endl;

}


void testCluster()
{
    cout<<"Testing cluster controller"<<endl;
    bool referenceFailed=false; // used to track reference unit tests
    Board main;
    cout<<"board created"<<endl;
    Square *row[9];
    Square *col[9];
    Square *box[9];
    cout<<"creating square groups"<<endl;
    //Cluster A;
    for (int k = 0; k < 9; k++)
    {
        row[k] = &main.sub(3, k);
        col[k] = &main.sub(k, 2);
        box[k] = &main.sub((k / 3), k % 3);
    }
    cout<<"squares created"<<endl;
    Cluster Row(CLUSTER_ROW, row);
    Cluster Col(CLUSTER_COL, col);
    Cluster Box(CLUSTER_BOX, box);
    cout<<"Clusters created"<<endl;



    main.sub(3,5).mark('5');
    //---------------------------------------------
    // based on the above mark calls
    // it shouuld be impossible for Square[3,4] to
    // have a 5 in it's possibility list
    //---------------------------------------------
    // Make sure that row, column and box dont have a possibility
    if(main.sub(3,4).isPossible('5') || main.sub(2,5).isPossible('5') ||
    		main.sub(4,3).isPossible('5'))
       cout<<"  - shoop test failed"<<endl;
    else
       cout<<"  - shoop test succeeded."<<endl;

    cout<<"Testing unshoop..."<<endl;
    main.sub(3,5).mark('1');
    // Make sure that row, column and box HAVE the possiblity back
    if(main.sub(3,4).isPossible('5') && main.sub(2,5).isPossible('5') &&
    		main.sub(4,3).isPossible('5'))
       cout<<"  - unshoop test succeeded."<<endl;
    else
       cout<<"  - unsoop test failed."<<endl;
    
    // I should be able to determine that a square is referencing
    // a possibility

    cout<<"Testing cluster references"<<endl;
    cout<<"  - testing row"<<endl;
    // check the entire row
    for(int k=0;k<9;k++)
    {
    	if(!main.sub(3,k).isReferenced(1))
    	{
    		cout<<"    test failed"<<endl;
    		referenceFailed = true;
    		break;
    	}
    }
    if(!referenceFailed)
    	cout<<"    test succeeded."<<endl;
    referenceFailed=false;
    //check the entire column
    cout<<"  - testing column"<<endl;
    for(int k=0;k<9;k++)
    {
    	if(!main.sub(k,5).isReferenced(1))
    	{
    		cout<<"    test failed."<<endl;
    		referenceFailed = true;
    		break;
    	}
    }
    if(!referenceFailed)
    	cout<<"    test succeeded."<<endl;


    //---------------------------------------------
    // Fault tolerant tests
    //---------------------------------------------
    cout<<"Functionality and Shoop Tests completed satisfactory"<<endl;
    cout<<"Testing throwing faults"<<endl;
    try {
      // The code below references a bad pointer
      // and throws a fatal exception as it should
      Square *tooshort[9];
      for(int k=0;k<9;k++)
    	  tooshort[k]=NULL;
      bzero(tooshort,9);
      for(int k=0;k<6;k++)
      {
          tooshort[k] = &main.sub(1,k);
      }
      Cluster tshort(CLUSTER_ROW,tooshort);
      cout<<tshort<<endl;

    } catch(FatalException &fe) {
       cout<<"  - test successful."<<endl;
       cout<<fe<<endl;
    }
    
}

//-----------------------------------------------------------------------------
// testTogether()
// Deprecated do not use
void testTogether()
{
    char game[] = { 0, 0, 0, 2, 6, 0, 7, 0, 1, 6, 8, 0, 0, 7, 0, 0, 9, 0, 1, 9,
            0, 0, 0, 4, 5, 0, 0, 8, 2, 0, 1, 0, 0, 0, 4, 0, 0, 0, 4, 6, 0, 2,
            9, 0, 0, 0, 5, 0, 0, 0, 3, 0, 2, 8, 0, 0, 9, 3, 0, 0, 0, 7, 4, 0,
            4, 0, 0, 5, 0, 0, 3, 6, 7, 0, 3, 0, 1, 8, 0, 0, 0 };

    int n = sizeof(game) / sizeof(game[0]);
    Board board;
    for (int k = 0; k < n; k++)
    {
        cout << "(" << k / 9 << "," << k % 9 << ")" << endl;
        if (game[k] == 0)
            continue;

        board.sub(k / 9, k % 9).mark(game[k] + '0');
    }
    cout << board << endl;
    board.printGUI(cout);
    cout << "I want to put an 8 in the lower right corner" << endl;
    board.sub(8, 8).mark('8');
    cout << "Since that didn't work let's try to put a nine there..." << endl;
    board.sub(8, 8).mark('9');
    cout << "Yay that worked, and here's what I get:" << endl;
    board.printGUI(cout);
}
