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
    if (!input.fail())
        loadGame();

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
        cerr << "Frame stack is empty" << endl;
        return;
    }
    frame = frames.top();
    frames.pop();
    board.restoreState(frame);
    delete frame;
}

//-----------------------------------------------------------------------------
// loadGame()
// As the name suggests
void Game::loadGame()
{
    Frame *frame = new Frame;
    for (int k = 0; k < 81; k++)
    {
        char c;
        input >> c;
        frame->states[k].mark(c);
    }
    board.restoreState(frame);

    frames.push(frame);

}
//-----------------------------------------------------------------------------
// saveGame()
// saves the game to the desired file
void Game::saveGame(const string &filename)
{
    Frame *currentFrame;
    ofstream output(filename.c_str(), ofstream::out);
    if (frames.empty())
        return;
    currentFrame = frames.top();
    for (int k = 0; k < 81; k++)
        output << currentFrame->states[k].getValue() << " ";

    output.close();

}

ostream& Game::print(ostream &out)
{
    board.printGUI(out);
    return out;
}

static void printMenu()
{
    cout << "Enter a choice: " << endl << "\t(1) Print Board" << endl
            << "\t(2) Go Back" << endl << "\t(3) Change a Square" << endl
            << "\t(4) Get Square " << endl << "\t(5) Quit " << endl;

}

void Game::run()
{
    char choice;

    do
    {
        printMenu();
        cout << "Enter a choice: " << endl;
        cin >> choice;
        switch (choice)
        {
        case '1':
            cout << *this << endl;
            break;
        case '2':
            popFrame();
            cout << *this << endl;
            break;
        case '3':
            changeSquare();
            cout << *this << endl;
            break;
        case '4':
            getSquare();
            break;

        default:
            return;
        }
    } while (choice >= '1' && choice <= '4');
}

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
    if (!board.sub(r - '1', c - '1').mark(val))
        // the Mark is illegal and so we go back
        popFrame();
}
