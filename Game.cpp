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
    input.open(filename.c_str(), ifstream::in);

}

Game::~Game()
{

}
