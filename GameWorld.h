#ifndef _GAMEWORLD_H_
#define _GAMEWORLD_H_

#include <iostream>
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
        int points;
    public:
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

int getKeyControls();

void controlEventHandler(int key, GameWorld *game);

#endif // _GAMEWORLD_H_