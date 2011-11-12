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



class Game
{
private:
    Board board;
    ifstream input; // the file loaded which contains the game
    stack<Frame *> frames;
    void pushFrame();
    void popFrame();

public:
    Game();
    Game(const string &filename);
    ~Game(); // I do not intend to derive from this class

    void loadGame();
    void saveGame(const string&);
    ostream& print(ostream &);

    void changeSquare();
    void getSquare();
    void run();

};

inline ostream& operator<<(ostream &out, Game &game)
{
    return game.print(out);
}

#endif /* GAME_HPP_ */
