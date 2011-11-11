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
    // Clear the stack of frames
    while(!frames.empty())
    {
        Frame *ptr = frames.top();
        frames.pop();
        if(ptr)
            delete ptr;
    }
}


void Game::pushFrame()
{
    Frame *frame = new Frame;
    board.saveState(frame);
    frames.push(frame);
}

void Game::loadGame()
{
    Frame *frame = new Frame;
    for(int k=0;k<81;k++)
    {
        char c;
        input>>c;
        frame->states[k].mark(c);
    }
    board.restoreState(frame);
    frames.push(frame);
}

void Game::saveGame(const string &filename)
{
    Frame currentFrame;
    ofstream output(filename.c_str(),ofstream::out);
    board.saveState(&currentFrame);

    for(int k=0;k<81;k++)
    {
        output<<currentFrame.states[k].getValue()<<" ";
    }
}

ostream& Game::print(ostream &out)
{
    board.printGUI(out);
    return out;
}
