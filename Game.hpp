//Game.hpp
// Luke Campbell
// 11 Nov 11
// Contains the Declaration of the Game class

#ifndef GAME_HPP_
#define GAME_HPP_

#include <iostream>
#include <stack>
#include <sstream>
#include "Board.hpp"
#include "DiagBoard.hpp"
#include "SquareState.hpp"
#include "SudokuStack.hpp"
#include "BadMove.hpp"
#include "MemoryManagement.hpp"

using namespace std;


// A class to model the and encapsulate the sudoku objects into an
// interactive game with the ability to save and restore game states
// and go backward to previous states.
class Game : public MemoryManagement
{
private:
    static int referenceCount;
protected:
    Board *board;
    ifstream input; // the file loaded which contains the game

    SudokuStack<Frame *> frames;
    void pushFrame();
    void popFrame();

    void printMenu();
    void printGameSubMenu();
    void selectCluster();
    void handleCluster(Cluster *);
    bool diagonalGame;

public:
    // Builds a blank game
    Game();
    // Builds a game using the specified file
    Game(const string &filename);

    // Frees all the frames in the stack
    ~Game();

    // Starts a blank new game
    void newGame(bool diagonal=false);

    // Returns the reference count of this class
    static int refCount() { return referenceCount; }


    // Loads a game from the specified file
    // Depracated supports old file type
    // and the filetype used in Sudokumm
    void loadGame(const string&);

    // Support for alternative file types
    void loadGame2(const string&);

    // Saves the current game state to the specified filename
    void saveGame(const string&);

    // Prints the current board state graphically
    ostream& print(ostream &);

    // interactive method to change a square's state
    void changeSquare();

    // interactive method to retrieve a square's state
    void getSquare();

    // main application loop
    // run() loops and interacts with the user
    void run();

};
// Overloaded operator to allow easy output
inline ostream& operator<<(ostream &out, Game &game)
{
    return game.print(out);
}

#endif /* GAME_HPP_ */
