//Game.hpp
// Luke Campbell
// 11 Nov 11
// Contains the Declaration of the Game class

#ifndef GAME_HPP_
#define GAME_HPP_

#include <iostream>
#include <stack>
#include "Board.hpp"
#include "SquareState.hpp"

using namespace std;


// A class to model the and encapsulate the sudoku objects into an
// interactive game with the ability to save and restore game states
// and go backward to previous states.
class Game
{
private:
    Board board;
    ifstream input; // the file loaded which contains the game
    stack<Frame *> frames;
    void pushFrame();
    void popFrame();

    void printMenu();
    void printGameSubMenu();

public:
    // Builds a blank game
    Game();
    // Builds a game using the specified file
    Game(const string &filename);

    // Frees all the frames in the stack
    ~Game();

    // Starts a blank new game
    void newGame();


    // Loads a game from the specified file
    void loadGame(const string&);

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
