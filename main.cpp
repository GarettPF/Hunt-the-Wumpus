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

    GameWorld world;
    do {
        new (&world) GameWorld();
        world.displayEntireWorld();
    } while (world.isPossible() != true);

    return 0;
}