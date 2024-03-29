// Game.cpp
// Luke Campbell
// 11 Nov 11
// Contains the definition for the Game class

#include <iostream>
#include "Game.hpp"

using namespace std;

int Game::referenceCount(0);


//-----------------------------------------------------------------------------
// Game()
// Constructs a blank game with a blank board
Game::Game()
{
   diagonalGame = false;
   board = new Board();
   referenceCount++;
}

//-----------------------------------------------------------------------------
// Game()
// Constructs a game and loads a file from filename
Game::Game(const string &filename)
{
   diagonalGame = true;
   loadGame(filename);
   referenceCount++;

}
//-----------------------------------------------------------------------------
// ~Game()
// Destructor for Game, clears the stack of frames
Game::~Game()
{
    // Clear the stack of frames
    while (!frames.empty())
    {
        Frame *ptr = frames.top();
        frames.pop();
        if (ptr)
            delete ptr;
    }
    delete board;
    referenceCount--;
}
//-----------------------------------------------------------------------------
// pushFrame()
// pushes the current
void Game::pushFrame()
{
    Frame *frame = new Frame;
    board->saveState(frame);
    frames.push(frame);
}
//-----------------------------------------------------------------------------
// popFrame()
// pops the current frame
void Game::popFrame()
{
    Frame *frame;
    if (frames.empty())
    {
        cerr << "Can't go back any futher" << endl;
        return;
    }
    frame = frames.top();
    frames.pop();
    board->restoreState(frame);
    delete frame;
}

//-----------------------------------------------------------------------------
// loadGame()
// Loads a game state from the specified filename
void Game::loadGame(const string& filename)
{
    if(input.is_open())
        input.close();
    input.open(filename.c_str(),ifstream::in);
    if(input.fail())
    {
        cerr<<"File: " << filename <<endl;
        cerr<<"Load failed"<<endl;

        return;
    }
    newGame();
    Frame *frame = new Frame;
    for (int k = 0; k < 81; k++)
    {
        char c;
        input >> c;
        try {
        	frame->states[k].forceMark(c);
         if(c>='1' && c<='9')
            frame->states[k].setConst();
        } catch(BadMove &b) {
        	cerr<<b<<endl;
        }
    }
    board->restoreState(frame);

    frames.push(frame);
}
//-----------------------------------------------------------------------------
// loadGame2()
// Loads a file of an alternative type
void Game::loadGame2(const string& filename)
{
    char diagonalFlag;
    string line;
    if(input.is_open())
        input.close();
    input.open(filename.c_str(), ifstream::in);
    if(input.fail())
    {
        cerr<<"File: "<<filename<<endl;
        cerr<<"Load failed"<<endl;
        return;
    }
    input>>diagonalFlag;
    getline(input,line);
    if(diagonalFlag == 't' || diagonalFlag == 'T')
    {
       newGame(); //Traditional Game
       cout<<"Traditional Game"<<endl;
    }
    else if(diagonalFlag == 'd' || diagonalFlag =='D')
    {
       newGame(true); // supports diagonal
       cout<<"Diagonal Game"<<endl;
    }
    else
    {
       throw FatalException("Game::loadGame2(): Improperly formatted file.");
    }
    Frame *frame = new Frame;
    for(int x=0;x<9 && !input.eof();x++)
    {
        stringstream errlines;
        getline(input,line);
        for(int y=0;y<9;y++)
        {
            char c = line[y];
            try {
            	frame->states[x*9 + y].forceMark(c);
               if(c>='1' && c<='9')
                  frame->states[x*9 + y].setConst();
            } catch(BadMove &b) {
            	errlines<<b<<endl;
            }
        }
        cout<<line<<endl;
        cerr<<errlines.str();
    }
    if(!input.eof())
    {
        string comments;
        while(!input.eof())
        {
            getline(input,comments);
            cout<<comments<<endl;
        }
    }
    cout<<"----File Loaded------"<<endl;
    board->restoreState(frame);
    frames.push(frame);
}
//-----------------------------------------------------------------------------
// saveGame()
// saves the game to the desired file
void Game::saveGame(const string &filename)
{
    Frame *currentFrame;
    pushFrame(); // Push the frame so that we may go back to it etc.
    ofstream output(filename.c_str(), ofstream::out);
    if (frames.empty())
        return;
    currentFrame = frames.top();
    for (int k = 0; k < 81; k++)
    {
       if(k%9==0 && k!=0)
          output<<endl;
        output << currentFrame->states[k].getValue();
    }
    output.close();

}

//-----------------------------------------------------------------------------
// print()
// Prints the current graphical board
ostream& Game::print(ostream &out)
{
    board->printGUI(out);
    return out;
}
//-----------------------------------------------------------------------------
// newGame()
// Pushes the current frame then clears the board
void Game::newGame(bool diagonal)
{
    // delete the board because we may have a new
    // variation of the sudoku game
    delete board; 
    if(diagonal)
       board = new DiagBoard();
    else
       board = new Board();
    diagonalGame = diagonal;
    pushFrame();
    for(int i=0;i<81;i++)
    {
    	try {
    		board->sub(i/9,i%9).mark('-');
    	} catch ( BadMove &b) {
    		cerr<<b<<endl;
    	}
    }

}
//-----------------------------------------------------------------------------
// printMenu()
// Displays a selection menu
void Game::printMenu()
{
    cout<<" Game Menu "<<endl
        <<" \\__ (1) Print Board" <<endl
        <<" \\__ (2) Go Back" <<endl
        <<" \\__ (3) Change a Square" <<endl
        <<" \\__ (4) Get Square" <<endl
        <<" \\__ (5) Game Option" <<endl
        <<" \\__ (6) Select a Cluster" <<endl
        <<" \\__ (7) Quit"<<endl ;

}
//-----------------------------------------------------------------------------
// printGameSubMenu()
// Displays and accepts user input for the Game submenu
// which includes saving, loading and a new game
void Game::printGameSubMenu()
{
    char input;
    string buffer;
    // The menu to be displayed
    cout<<"\t\\__ (1) New Game" << endl
        <<"\t\\__ (2) Save Game" << endl
        <<"\t\\__ (3) Load Game " << endl
        <<"\t\\__ (4) Go Back" <<endl;
    cout<<"Enter a choice: ";
    cin>>input;

    // Handle the user's response
    switch(input)
    {
    case '1': // New Game
        cout<<"New game"<<endl;
        cout<<"(T) Tradtional or (D) Diagonal: ";
        cin>>input;
        if(input == 'd' || input == 'D')
        {
           newGame(true);
           cout<<"Diagonal Game"<<endl;
        }
        else if(input=='t' || input=='T')
        {
           newGame(false);
           cout<<"Traditional Sudoku"<<endl;
        }
        else
           cerr<<"Invalid choice"<<endl;
        break;
    case '2': // Save Game
        cout<<"Save Game"<<endl;
        cout<<"Enter filename: ";
        cin.get(); // clears newline in buffer
        getline(cin,buffer);
        saveGame(buffer);
        break;
    case '3':  // Load Game
        cout<<"Load Game"<<endl;
        cout<<"Enter filename: ";
        cin.get(); // clears the newline
        getline(cin,buffer);
        loadGame2(buffer);
        break;
    default: // Go back
        return;
    }
}
//-----------------------------------------------------------------------------
// selectCluster()
// Allows the user to select a cluster in the game
void Game::selectCluster()
{
   Cluster *cluster;
   char choice;
   cout<<"\t\\__ (1) Row Cluster"<<endl;
   cout<<"\t\\__ (2) Column Cluster"<<endl;
   cout<<"\t\\__ (3) Box Cluster"<<endl;
   if(diagonalGame)
      cout<<"\t\\__ (4) Diagonal Cluster"<<endl;
   cout<<"Enter a choice: ";
   cin>>choice;
   //-------------------------------------------
   // I deliberately did not use a switch case
   // because of all the code between each case
   // I don't like using try/catch and object
   // manipulation in switch cases.
   //-------------------------------------------
   if(choice == '1')
   {
      cout<<"Enter a row: ";
      cin>>choice;
      try {
         cluster = board->getCluster(CLUSTER_ROW,choice-'1');
      } catch(FatalException &fe) {
         cerr<<"Bad Selection"<<endl;
         return;
      }
   }
   else if(choice == '2')
   {
      cout<<"Enter a column: ";
      cin>>choice;
      try {
         cluster = board->getCluster(CLUSTER_COL,choice-'1');
      } catch(FatalException &fe) {
         cerr<<"Bad Selection"<<endl;
         return;
      }
   }
   else if(choice == '3')
   {
      cout<<"Enter a box: ";
      cin>>choice;
      try {
         cluster = board->getCluster(CLUSTER_BOX,choice-'1');
      } catch(FatalException &fe) {
         cerr<<"Bad Selection"<<endl;
         return;
      }
   }
   else if(diagonalGame && choice=='4')
   {
      cout<<"Enter a diagonal"<<endl;
      cout<<"(1) Upper Left to Lower Right"<<endl;
      cout<<"(2) Upper Right to Lower Left"<<endl;
      cout<<"Enter a choice: ";
      cin>>choice;
      try {
         cluster = board->getCluster(CLUSTER_DIAGONAL,choice-'1');
      } catch(FatalException &fe) {
         cerr<<"Bad Selection"<<endl;
         return;
      }
   }
   else 
   {
      cout<<"Invalid Selection"<<endl;
      return;
   }
   handleCluster(cluster);
   return;

}
//-----------------------------------------------------------------------------
// handleCluster()
// Provides the interface between the user and the cluster
// This method is really convoluted because of the nested
// interfaces to the user
void Game::handleCluster(Cluster *cluster)
{
   char choice=0;
   Square *square = NULL;
   if(!cluster)
      throw FatalException("Game::handleCluster() null pointer\n");
   cout<<endl<<*this<<endl;
   cout<<*cluster<<endl;
   cout<<"(1): Change a square"<<endl
       <<"(2): Go back"<<endl;
   cout<<"Enter a choice: ";
   cin>>choice;
   //--------------------------------
   // Handle a square selection
   //--------------------------------
   if(choice=='1')
   {
      cout<<"Select a square: ";
      cin>>choice;
      if(choice>='1' && choice<='9')
      {
         try {
            square = cluster->getSquare(choice-'1');
         } catch (FatalException &fe) {
            cout<<"Error has occurred: "<<fe<<endl;
            return;
         }
         cout<<*square<<endl;
         cout<<"Enter a value: ";
         cin>>choice;
         //--------------------------------
         // mark the square
         //--------------------------------
         try {
            pushFrame();
            square->mark(choice);
         } catch(BadMove &bm) {
            cout<<bm<<endl;
            return;
         } catch(FatalException &fe) {
            cerr<<"Something has gone wrong."<<endl;
            cerr<<fe<<endl;
            return;
         }


      }
      else
      {
         cout<<"Invalid Selection"<<endl;
         return;
      }
   }

}
//-----------------------------------------------------------------------------
// run()
// The main loop which interacts with the user prompting actions and displaying
// the interfaces
void Game::run()
{
    char choice;
    do
    {
        cout<<endl<<*this<<endl;
        printMenu();
        cout << "Enter a choice: ";
        cin >> choice;
        switch (choice)
        {
        case '1': // Print Board
            break;
        case '2': // Go back
            popFrame();
            break;
        case '3': // Change a Square
            changeSquare();
            break;
        case '4': // Get A Square
            getSquare();
            break;
        case '5': // Game Submenu
            printGameSubMenu();
            break;
        case '6': // Cluster Menu
            selectCluster();
            break;
        default:
            return;
        }
    } while (choice >= '1' && choice <= '6');
}
//-----------------------------------------------------------------------------
// getSquare()
// An interactive method to retrieve the Square's state based on the user's
// responses
void Game::getSquare()
{
    char r, c;
    cout << "Enter the row: ";
    cin >> r;
    if (r < '1' || r > '9')
    {
        cerr << "Invalid entry" << endl;
        return;
    }
    cout << "Enter the column: ";
    cin >> c;
    if (c < '1' || c > '9')
    {
        cerr << "Invalid entry" << endl;
        return;
    }
    cout << board->sub(r - '1', c - '1') << endl;

}
//-----------------------------------------------------------------------------
// chagneSquare()
// Allows the user to change the state of a desired square based on user's
// response
void Game::changeSquare()
{
    char r, c, val;
    cout << "Enter the row: ";
    cin >> r;
    if (r < '1' || r > '9')
    {
        cerr << "Invalid entry" << endl;
        return;
    }
    cout << "Enter the column: ";
    cin >> c;
    if (c < '1' || c > '9')
    {
        cerr << "Invalid entry" << endl;
        return;
    }
    cout<<board->sub(r-'1',c-'1')<<endl;
    cout << "Enter the value: ";
    cin >> val;

    // Push the frame

    pushFrame();
    try {
		if (!board->sub(r - '1', c - '1').mark(val))
			// the Mark is illegal and so we go back
			popFrame();
    } catch(BadMove &b) {
    	cerr<<b<<endl;
    }
}
