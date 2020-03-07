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

    int key = 0;
    const string quit = "qQ";
    bool done = false,
         won = false, 
         alive = true;
    ofstream scores("GameScores.txt");
    if (!scores.is_open())
        return -1;
    string name;

    while (!done) {
        won = false;
        alive = true;
        cout << "Enter your name: ";
        cin >> name;

        // Creates a world that is possible to win
        GameWorld world;
        do {
            new (&world) GameWorld();
        } while (!world.isPossible());

        world.playerName = name;

        while (!done && !won && alive) {         // game loop
            // display current world
            CLS;
            world.displayWorld();

            // get control events
            key = getKeyControls();
            controlEventHandler(key, &world);

            // check game events
            won = world.haveIWon();
            alive = world.amIAlive();

            world.update();

            if (quit.find(key) != string::npos) done = true;
        }

        // log results
        if (won) {
            writeToFile(scores, world, "Won");
            cout << "You won " << world.playerName << endl;
            world.displayEntireWorld();
        }
        else if (!alive) {
            writeToFile(scores, world, "Died");
            cout << "You died " << world.playerName << endl;
            world.displayEntireWorld();
        }
        if (!done) {
            char answer;
            do {
                cout << "Do you want to play again (Y/n): ";
                cin >> answer;
            } while (answer != 'Y' && answer != 'y' && answer != 'n');
            if (answer == 'n')
                done = true;
        }
    }

    CLS;
    cout << "Come again!" << endl;
    scores.close();
    return 0;
}