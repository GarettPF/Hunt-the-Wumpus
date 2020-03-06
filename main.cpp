/**************************************************************
* Programmer: Garett Pascual-Folster					      *
* Class: CptS 122, Spring, 2020; Lab Section 4			      *
* Programming Assignment: PA4							      *
* Date: March 2, 2020							    	      *
* Description: This a recreation of the game Hunt the Wumpus  *
***************************************************************/

#include "GameWorld.h"

int main() {
    srand(time(NULL));
    system("cls");

    int key = 0, done = 0;
    string quit = "qQ";
    bool won = false, 
         alive = true;

    // Creates a world that is possible to win
    GameWorld world;
    do {
        new (&world) GameWorld();
    } while (!world.isPossible());


    while (!done && !won && alive) {
        // display current world
        CLS;
        world.displayEntireWorld();

        // get control events
        key = getKeyControls();
        controlEventHandler(key, &world);

        // check game events
        won = world.haveIWon();
        alive = world.amIAlive();


        world.update();

        if (quit.find(key) != string::npos) done = 1;
    }

    return 0;
}