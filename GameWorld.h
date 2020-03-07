#ifndef _GAMEWORLD_H_
#define _GAMEWORLD_H_

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <ctime>
#include <conio.h>
using namespace std;

#define CLS system("cls")
#define PAUSE system("pause")

#define N_ROW 5
#define N_COL 5

struct Location {
    int row;
    int col;
};

class GameWorld {
    private:
        char map[N_ROW][N_COL] = {{'\0'}};
        Location pos;
    public:
        int points;
        string playerName;
        
        // Constructor
        GameWorld();

        // display
        void displayWorld() const;         // show player only
        void displayEntireWorld() const;   // cheat function
        void displayVisibleWorld() const;  // show adjacent spots

        // controls
        void moveUp();
        void moveDown();
        void moveRight();
        void moveLeft();

        // game event checking
        bool haveIWon() const;
        bool amIAlive() const;
        bool isPossible();

        // refresh map
        void update();
};

/*
Function: getKeyControls
Description: Used as a way to get key strokes from the user
    @param void
    @return the key ascii value
*/
int getKeyControls();

/*
Function: controlEventHandler
Description: Determines what to do with the given key input
    @param key      the key ascii value
    @param *game    The address of the current game to change
    @return void
*/
void controlEventHandler(int key, GameWorld *game);

/*
Function: writeToFile
Description: write the game results to the results file
    @param outfile  the output file stream
    @param game     the game results
    @param status   the status of the game
*/
void writeToFile(ofstream& outfile, GameWorld game, string status);

#endif // _GAMEWORLD_H_