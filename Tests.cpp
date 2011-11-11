// Tests.cpp
// Lucas Campbell
// 1 Oct 2011
// Contains the testing functions

#include "Sudoku.hpp"
#include "Square.hpp"
#include "Board.hpp"
#include "Cluster.hpp"

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

//-----------------------------------------------------------------------------
// testBoard()
// Performs an array of tests on the Board class
// no arguments
// no return
void testBoard()
{
    Square *buf; // buffer variable for testing
    // First test, attempt to load a bad filename

    //    cout<<"-------------------------------------------"<<endl<<endl;
    //    cout<<"    Error Test"<<endl;
    //    cout<<" Various error testing (commented)"<<endl<<endl;;
    //    cout<<"-------------------------------------------"<<endl;

    // Bad input filename
    //Board error("BADFILE");

    // Bad subscript
    //  Board error("INPUT");
    // Bad first index
    //  error.sub(9,4);
    // Bad second index
    //  error.sub(4,9);
    // Negative index
    //     error.sub(-1,9);

    // Bad marking on a Square
    //     Square badsquare(0,0);
    // mark a non numeric value
    //     cout<<"mark 'a'"<<endl;
    //     badsquare.mark('a');
    //     cout<<badsquare<<endl;
    // turn off something outside 1-9
    //     badsquare.turnOff(0);
    //     cout<<"turnOff 0"<<endl;
    //     cout<<badsquare<<endl;
    //     cout<<"turnOff 11"<<endl;
    //     badsquare.turnOff(11);
    //     cout<<badsquare<<endl;


    // Second actually make a Board and test various subscripts
    Board second("INPUT");

    cout << "-------------------------------------------" << endl << endl;
    cout << "    Second Test" << endl;
    cout << " Subscript testing" << endl << endl;
    ;
    cout << "-------------------------------------------" << endl;

    cout << "First square is [0,0]: " << second.sub(0, 0) << endl;
    // Now try changing the value of that square
    buf = &second.sub(0, 0);
    buf->mark('1');
    buf->turnOff(1);
    cout << "First square is now changed: " << *buf << endl;
    cout << "Requested subsequent square: " << second.sub(0, 0) << endl;

    // Now change the subscript [4,4]
    cout << "Changing Square[4,4] to a 5" << endl;
    buf = &second.sub(4, 4);
    buf->mark('5');
    buf->turnOff(5);
    cout << *buf << endl;

    // Now change the last subscript Square[8,8]
    cout << "Changing Square[8,8] to a 9" << endl;
    buf = &second.sub(8, 8);
    buf->mark('9');
    buf->turnOff(9);
    cout << *buf << endl;

    cout << "-------------------------------------------" << endl << endl;
    cout << "    Third Test" << endl;
    cout << " Printing the board" << endl << endl;
    cout << "-------------------------------------------" << endl;
    cout << " This is the board from the second test:" << endl;
    cout << second << endl;
}

void testCluster()
{
    Board main;
    Square *row[9];
    Square *col[9];
    Square *box[9];
    //Cluster A;
    for (int k = 0; k < 9; k++)
    {
        row[k] = &main.sub(3, k);
        col[k] = &main.sub(k, 2);
        box[k] = &main.sub((k / 3), k % 3);
        //cout<<*box[k]<<endl;
    }
    Cluster Row(CLUSTER_ROW, row);
    Cluster Col(CLUSTER_COL, col);
    Cluster Box(CLUSTER_BOX, box);

    Row.shoop(&main.sub(3, 5), '5');
    Col.shoop(&main.sub(2, 2), '6');
    Box.shoop(&main.sub(1, 1), '2');

    cout << Row << endl << Col << endl << Box << endl;

    main.sub(2, 3).mark('2');
    cout << main << endl;
    //    The below code causes a SEGFAULT
    //    Square *tooshort[9];
    //    bzero(tooshort,9);
    //    for(int k=0;k<6;k++)
    //    {
    //        tooshort[k] = &main.sub(1,k);
    //    }
    //    Cluster tshort(CLUSTER_ROW,tooshort);
    //    cout<<tshort<<endl;

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
