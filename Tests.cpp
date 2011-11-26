// Tests.cpp
// Lucas Campbell
// 1 Oct 2011
// Contains the testing functions

#include <typeinfo>

#include "Sudoku.hpp"
#include "Square.hpp"
#include "Board.hpp"
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

	try {
		cout<<" - testing accessor out of bounds"<<endl;
		cluster = myBoard.getCluster(CLUSTER_ROW,10); // out of bounds
		
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
    // Test basic initialization
    Square first(0, 0);

    // Test basic output of this square
    cout << first << endl;

    // Test initialization with NEGATIVE values for row and col
    // since I declared row and col as unsigned, it should be
    // extremely large numbers (two's complement)
    Square second(-30, -90);
    cout << second << endl;

    // Test initialization with sufficiently large integers
    Square third(0xFFFFFFFF, 0xFFFFFFFF);
    cout << third << endl;

    // Try to overflow the class
    Square fourth(0xFFFFFFFF + 1, 0xFFFFFFFF + 1);
    cout << fourth << endl;
}
void testBoard()
{

   Board board;
   cout<<"Testing Board"<<endl;
   // it should generate a Board with the default constructor
   // it should allow a mark in any square within the boards bounds
   try {
      board.sub(8,8).mark('1');
   } catch (BadMove &b) {
      cout<<"  - test failed."<<endl;
      cerr<<"Board Test Failed"<<endl
          <<"  - it should allow a mark in any square"<<endl;
      return;
   }
   cout<<"  - test succeeded."<<endl;
   

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


}
//-----------------------------------------------------------------------------
// testBoard()
// Performs an array of tests on the Board class
// no arguments
//// no return
//void testBoard()
//{
//    Square *buf; // buffer variable for testing
//    // First test, attempt to load a bad filename
//
//    //    cout<<"-------------------------------------------"<<endl<<endl;
//    //    cout<<"    Error Test"<<endl;
//    //    cout<<" Various error testing (commented)"<<endl<<endl;;
//    //    cout<<"-------------------------------------------"<<endl;
//
//    // Bad input filename
//    //Board error("BADFILE");
//
//    // Bad subscript
//    //  Board error("INPUT");
//    // Bad first index
//    //  error.sub(9,4);
//    // Bad second index
//    //  error.sub(4,9);
//    // Negative index
//    //     error.sub(-1,9);
//
//    // Bad marking on a Square
//    //     Square badsquare(0,0);
//    // mark a non numeric value
//    //     cout<<"mark 'a'"<<endl;
//    //     badsquare.mark('a');
//    //     cout<<badsquare<<endl;
//    // turn off something outside 1-9
//    //     badsquare.turnOff(0);
//    //     cout<<"turnOff 0"<<endl;
//    //     cout<<badsquare<<endl;
//    //     cout<<"turnOff 11"<<endl;
//    //     badsquare.turnOff(11);
//    //     cout<<badsquare<<endl;
//
//
//    // Second actually make a Board and test various subscripts
//    Board second("INPUT");
//
//    cout << "-------------------------------------------" << endl << endl;
//    cout << "    Second Test" << endl;
//    cout << " Subscript testing" << endl << endl;
//    ;
//    cout << "-------------------------------------------" << endl;
//
//    cout << "First square is [0,0]: " << second.sub(0, 0) << endl;
//    // Now try changing the value of that square
//    buf = &second.sub(0, 0);
//    buf->mark('1');
//    buf->turnOff(1);
//    cout << "First square is now changed: " << *buf << endl;
//    cout << "Requested subsequent square: " << second.sub(0, 0) << endl;
//
//    // Now change the subscript [4,4]
//    cout << "Changing Square[4,4] to a 5" << endl;
//    buf = &second.sub(4, 4);
//    buf->mark('5');
//    buf->turnOff(5);
//    cout << *buf << endl;
//
//    // Now change the last subscript Square[8,8]
//    cout << "Changing Square[8,8] to a 9" << endl;
//    buf = &second.sub(8, 8);
//    buf->mark('9');
//    buf->turnOff(9);
//    cout << *buf << endl;
//
//    cout << "-------------------------------------------" << endl << endl;
//    cout << "    Third Test" << endl;
//    cout << " Printing the board" << endl << endl;
//    cout << "-------------------------------------------" << endl;
//    cout << " This is the board from the second test:" << endl;
//    cout << second << endl;
//}

void testCluster()
{
    cout<<"Testing cluster controller"<<endl;
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

    Row.shoop(&main.sub(3, 5), '5');
    Col.shoop(&main.sub(2, 2), '6');
    Box.shoop(&main.sub(1, 1), '2');
    //---------------------------------------------
    // based on the above shoop calls
    // it shouuld be impossible for Square[3,4] to
    // have a 5 in it's possibility list
    //---------------------------------------------

    if(main.sub(3,4).isPossible('5'))
       cout<<"  - shoop test failed"<<endl;
    else
       cout<<"  - shoop test succeeded."<<endl;

    cout<<"Testing unshoop..."<<endl;
    Row.unshoop(&main.sub(3,5),'5');
    if(main.sub(3,4).isPossible('5'))
       cout<<"  - unshoop test succeeded."<<endl;
    else
       cout<<"  - unsoop test failed."<<endl;
    

    //---------------------------------------------
    // Fault tolerant tests
    //---------------------------------------------
    cout<<"Functionality and Shoop Tests completed satisfactory"<<endl;
    cout<<"Testing throwing faults"<<endl;
    try {
      // The code below references a bad pointer
      // and throws a fatal exception as it should
      Square *tooshort[9];
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
// Performs an array of tests on the Sudoku application
// no arguments
// no return
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
