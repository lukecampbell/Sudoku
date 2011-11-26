// Game.cpp
// Luke Campbell
// 11 Nov 11
// Contains the definition for the Game class

#include <iostream>
#include "Game.hpp"

using namespace std;
//-----------------------------------------------------------------------------
// Game()
// Constructs a blank game with a blank board
Game::Game()
{

}

//-----------------------------------------------------------------------------
// Game()
// Constructs a game and loads a file from filename
Game::Game(const string &filename)
{
    loadGame(filename);

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
}
//-----------------------------------------------------------------------------
// pushFrame()
// pushes the current
void Game::pushFrame()
{
    Frame *frame = new Frame;
    board.saveState(frame);
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
    board.restoreState(frame);
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
        	frame->states[k].mark(c);
        } catch(BadMove &b) {
        	cerr<<b<<endl;
        }
    }
    board.restoreState(frame);

    frames.push(frame);
}
//-----------------------------------------------------------------------------
// loadGame2()
// Loads a file of an alternative type
void Game::loadGame2(const string& filename)
{
    if(input.is_open())
        input.close();
    input.open(filename.c_str(), ifstream::in);
    if(input.fail())
    {
        cerr<<"File: "<<filename<<endl;
        cerr<<"Load failed"<<endl;
        return;
    }
    newGame();
    Frame *frame = new Frame;
    for(int x=0;x<9 && !input.eof();x++)
    {
        string line;
        getline(input,line);
        for(int y=0;y<9;y++)
        {
            char c = line[y];
            try {
            	frame->states[x*9 + y].mark(c);
            } catch(BadMove &b) {
            	cerr<<b<<endl;
            }
        }
        cout<<line<<endl;
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
    board.restoreState(frame);
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
        output << currentFrame->states[k].getValue() << " ";

    output.close();

}

//-----------------------------------------------------------------------------
// print()
// Prints the current graphical board
ostream& Game::print(ostream &out)
{
    board.printGUI(out);
    return out;
}
//-----------------------------------------------------------------------------
// newGame()
// Pushes the current frame then clears the board
void Game::newGame()
{
    pushFrame();
    for(int i=0;i<81;i++)
    {
    	try {
    		board.sub(i/9,i%9).mark('-');
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
        newGame();
        cout<<"New game"<<endl;
        cout<<*this<<endl;
        break;
    case '2': // Save Game
        cout<<"Save Game"<<endl;
        cout<<"Enter filename: ";
        cin.get(); // clears newline in buffer
        getline(cin,buffer);
        saveGame(buffer);
        cout<<*this<<endl;
        break;
    case '3':  // Load Game
        cout<<"Load Game"<<endl;
        cout<<"Enter filename: ";
        cin.get(); // clears the newline
        getline(cin,buffer);
        loadGame2(buffer);
        cout<<*this<<endl;
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

   cout<<"Enter a choice: ";
   cin>>choice;
   if(choice == '1')
   {
      cout<<"Enter a row: ";
      cin>>choice;
      try {
         cluster = board.getCluster(CLUSTER_ROW,choice-'1');
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
         cluster = board.getCluster(CLUSTER_COL,choice-'1');
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
         cluster = board.getCluster(CLUSTER_BOX,choice-'1');
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
   cout<<endl<<*this<<endl;
   cout<<*cluster<<endl;
   return;

}
//-----------------------------------------------------------------------------
// run()
// The main loop which interacts with the user prompting actions and displaying
// the interfaces
void Game::run()
{
    char choice;
    cout<<*this<<endl;
    do
    {
        printMenu();
        cout << "Enter a choice: ";
        cin >> choice;
        switch (choice)
        {
        case '1': // Print Board
            cout << *this << endl;
            break;
        case '2': // Go back
            popFrame();
            cout << endl << *this << endl;
            break;
        case '3': // Change a Square
            changeSquare();
            cout << endl << *this << endl;
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
    cout << board.sub(r - '1', c - '1') << endl;

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
    cout << "Enter the value: ";
    cin >> val;

    // Push the frame

    pushFrame();
    try {
		if (!board.sub(r - '1', c - '1').mark(val))
			// the Mark is illegal and so we go back
			popFrame();
    } catch(BadMove &b) {
    	cerr<<b<<endl;
    }
}
