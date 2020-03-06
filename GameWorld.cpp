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

void GameWorld::displayWorld() const {
    string legend[4] = {
        "W = Wumpus",
        "P = Pitt",
        "U = Player/User",
        "G = Gold"
    };
    string controls[11] = {
        "--- Controls ---\t\t--Points--",
        "i or I to move up   \t\t+5 points",
        "k or K to move down \t\t+5 points",
        "j or J to move left \t\t+5 points",
        "l or L to move right\t\t+5 points",
        "v or V to show nearby caves\t-2 points",
        "c or C to show entire world\t-5 points",
        " ",
        "r or R to restart the game with the same player",
        "n or N to restart the game with a new player",
        "q or Q to end the game"
    };

    // display game and legend
    cout << "+";
    for (int col = 0; col < N_COL; ++col) cout << "---";
    cout << "+" << endl;

    for (int row = 0; row < N_ROW; ++row) {
        cout << '|';
        for (int col = 0; col < N_COL; ++col) {
            cout << ' ';
            if (map[row][col] == 'U')
                cout << map[row][col];
            else
                cout << ' ';
            cout << ' ';
        }

        cout << "|";
        if (row != 4)
            cout << "\t" << legend[row];
        cout << endl;
    }

    cout << "+";
    for (int col = 0; col < N_COL; ++col) cout << "---";
    cout << "+" << endl << endl;

    // display controls
    for (int i = 0; i < 11; ++i) {
        cout << controls[i] << endl;
    }

    cout << endl << endl;
}

void GameWorld::displayEntireWorld() const {
    string legend[4] = {
        "W = Wumpus",
        "P = Pitt",
        "U = Player/User",
        "G = Gold"
    };
    string controls[11] = {
        "--- Controls ---\t\t--Points--",
        "i or I to move up   \t\t+5 points",
        "k or K to move down \t\t+5 points",
        "j or J to move left \t\t+5 points",
        "l or L to move right\t\t+5 points",
        "v or V to show nearby caves\t-2 points",
        "c or C to show entire world\t-5 points",
        " ",
        "r or R to restart the game with the same player",
        "n or N to restart the game with a new player",
        "q or Q to end the game"
    };

    // display game and legend
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
            cout << "\t" << legend[row];
        cout << endl;
    }

    cout << "+";
    for (int col = 0; col < N_COL; ++col) cout << "---";
    cout << "+" << endl << endl;

    // display controls
    for (int i = 0; i < 11; ++i) {
        cout << controls[i] << endl;
    }

    cout << endl << endl;
}

void GameWorld::displayVisibleWorld() const {
    string legend[4] = {
        "W = Wumpus",
        "P = Pitt",
        "U = Player/User",
        "G = Gold"
    };
    string controls[11] = {
        "--- Controls ---\t\t--Points--",
        "i or I to move up   \t\t+5 points",
        "k or K to move down \t\t+5 points",
        "j or J to move left \t\t+5 points",
        "l or L to move right\t\t+5 points",
        "v or V to show nearby caves\t-2 points",
        "c or C to show entire world\t-5 points",
        " ",
        "r or R to restart the game with the same player",
        "n or N to restart the game with a new player",
        "q or Q to end the game"
    };

    // display game and legend
    cout << "+";
    for (int col = 0; col < N_COL; ++col) cout << "---";
    cout << "+" << endl;

    for (int row = 0; row < N_ROW; ++row) {
        cout << '|';
        for (int col = 0; col < N_COL; ++col) {
            cout << ' ';
            if ((row + 1 == pos.row && col == pos.col) ||
                (row - 1 == pos.row && col == pos.col) ||
                (row == pos.row && col + 1 == pos.col) ||
                (row == pos.row && col - 1 == pos.col) ||
                (row + 1 == pos.row && col + 1 == pos.col) ||
                (row + 1 == pos.row && col - 1 == pos.col) ||
                (row - 1 == pos.row && col + 1 == pos.col) ||
                (row - 1 == pos.row && col - 1 == pos.col) ||
                (row == pos.row && col == pos.col))
                cout << map[row][col];
            else 
                cout << ' ';
            cout << ' ';
        }

        // legend
        cout << "|";
        if (row != 4)
            cout << "\t" << legend[row];
        cout << endl;
    }

    cout << "+";
    for (int col = 0; col < N_COL; ++col) cout << "---";
    cout << "+" << endl << endl;

    // display controls
    for (int i = 0; i < 11; ++i) {
        cout << controls[i] << endl;
    }

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
        else { // retrace steps if hit a dead end
            i -= 2 ;
            y = positions[i + 1].row;
            x = positions[i + 1].col;
        }

        if (map[y][x] == 'G') // at the gold
            possible = true;
        else if (i == 0)      // no possible path
            trapped = true;
        else
            map[y][x] = '1';
    }
    
    // clean up map
    x = 0; 
    y = 0;
    while (y != 5) {
        if (map[y][x] == '1')
            map[y][x] = '\0';
        
        y = (x == 4) ? y + 1 : y;
        x = (x == 4) ? 0 : x + 1;
    }

    map[pos.row][pos.col] = 'U';

    return possible;
}

void GameWorld::moveUp() {
    if (pos.row != 0)
        pos.row -= 1;
}

void GameWorld::moveDown() {
    if (pos.row != 4)
        pos.row += 1;
}

void GameWorld::moveRight() {
    if (pos.col != 4)
        pos.col += 1;
}

void GameWorld::moveLeft() {
    if (pos.col != 0)
        pos.col -= 1;
}

bool GameWorld::haveIWon() const {
    bool won = false;
    
    if (map[pos.row][pos.col] == 'G')
        won = true;

    return won;
}

bool GameWorld::amIAlive() const {
    bool alive = true;
    string waysToDie = "PW";

    if (waysToDie.find(map[pos.row][pos.col]) != string::npos)
        alive = false;

    return alive;
}


void GameWorld::update() {
    // locate old position
    int row = 0, col = 0;
    while (map[row][col] != 'U') {
        row = (col == 4) ? row + 1 : row;
        col = (col == 4) ? 0 : col + 1;
    }
    // remove old location
    map[row][col] = '\0';

    map[pos.row][pos.col] = 'U';
}

int getKeyControls() {
    char key = 0;
    do {
        key = getch();
    } while (
        key != 'i' && key != 'I' &&
        key != 'k' && key != 'K' &&
        key != 'j' && key != 'J' &&
        key != 'l' && key != 'L' &&
        key != 'v' && key != 'V' &&
        key != 'c' && key != 'C' &&
        key != 'r' && key != 'R' &&
        key != 'n' && key != 'N' &&
        key != 'q' && key != 'Q' 
    );
    return key;
}

void controlEventHandler(int key, GameWorld *game) {
    CLS;
    switch (key) {
        case 'i':
        case 'I':
            game->moveUp();
            break;
        case 'k':
        case 'K':
            game->moveDown();
            break;
        case 'j':
        case 'J':
            game->moveLeft();
            break;
        case 'l':
        case 'L':
            game->moveRight();
            break;
        case 'v':
        case 'V':
            CLS;
            game->displayVisibleWorld();
            PAUSE;
            break;
        case 'c':
        case 'C':
            CLS;
            game->displayEntireWorld();
            PAUSE;
            break;
        case 'r':
        case 'R':
            cout << "R pressed" << endl;
            break;
        case 'n':
        case 'N':
            cout << "N pressed" << endl;
            break;
    }
}