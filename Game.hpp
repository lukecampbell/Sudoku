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

public:
    Game();
    Game(const string &filename);
    ~Game(); // I do not intend to derive from this class


};

#endif /* GAME_HPP_ */
