#include "GameWorld.h"

GameWorld::GameWorld() {
    int n_pits = rand() % 6 + 5,
        row, col;
    char symbols[] = {'G','U','W'};

    // place the pits
    while (n_pits--) {
        do {
            row = rand() % 5;
            col = rand() % 5;
        } while (map[row][col] != '\0');

        map[row][col] = 'P';
    }

    // place the player, gold, and wumpus
    for (int i = 0; i < 3; ++i) {
        do {
            row = rand() % 5;
            col = rand() % 5;
        } while (map[row][col] != '\0');
        map[row][col] = symbols[i];
        if (i == 1) {
            pos.row = row;
            pos.col = col;
        }
    }
}

void GameWorld::displayEntireWorld() const {
    string legend[4] = {
        "W = Wumpus",
        "P = Pitt",
        "U = Player/User",
        "G = Gold"
    };

    cout << "+";
    for (int col = 0; col < N_COL; ++col) cout << "---";
    cout << "+" << endl;

    for (int row = 0; row < N_ROW; ++row) {
        cout << '|';
        for (int col = 0; col < N_COL; ++col) {
            cout << ' ' << map[row][col] << ' ';
        }

        cout << "|";
        if (row != 4)
            cout << "\t\t" << legend[row];
        cout << endl;
    }

    cout << "+";
    for (int col = 0; col < N_COL; ++col) cout << "---";
    cout << "+" << endl;

    cout << endl << endl;
}

bool GameWorld::isPossible() {
    bool possible = false, trapped = false;
    string symbols = "PW1";
    Location positions[625];

    // path finding algorithm
    int x = pos.col, y = pos.row, i = 0;
    while (!possible && !trapped) {
        i++;
        positions[i].row = y;
        positions[i].col = x;
        if (symbols.find(map[y + 1][x]) == string::npos && y != 4) // going down
            y += 1;
        else if (symbols.find(map[y - 1][x]) == string::npos && y != 0) // going up
            y -= 1;
        else if (symbols.find(map[y][x + 1]) == string::npos && x != 4) // going right
            x += 1;
        else if (symbols.find(map[y][x - 1]) == string::npos && x != 0) // going left
            x -= 1;
        else { // start a new path if hit a dead end
            i -= 2 ;
            y = positions[i + 1].row;
            x = positions[i + 1].col;
        }
        if (map[y][x] == 'G')
            possible = true;
        if (i == 0)
            trapped = true;

        map[y][x] = '1';
        displayEntireWorld();
        cout << y << ' ' << x << ' ' << i << endl;
        PAUSE;
    }
    
    // clean up map
    x = 0; 
    y = 0;
    while (y != 5) {
        if (map[y][x] == '1')
            map[y][x] = '\0';
        
        x = (x == 4) ? 0 : x + 1;
        y++;
    }

    map[pos.row][pos.col] = 'U';

    return possible;
}