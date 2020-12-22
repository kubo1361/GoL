//
// Created by Eternal on 22/12/2020.
//

#include "Menu.h"

Menu::Menu() {
}

Menu::~Menu() {
    delete game;
}

void Menu::start() {
    int rows;
    int cols;
    int startMethod;
    int x;
    int y;
    int count;
    string filename;
    string confirm;

    cout << "Welcome to Game of Life" << endl;
    cout << "-----------------------" << endl;
    cout << "O - living cell" << endl;
    cout << ". - dead cell" << endl;
    cout << "-----------------------" << endl;
    cout << endl;


    do {
        cout << "Select a method for preparing starting conditions for your world: " << endl;
        cout << "1. Define living cells yourself" << endl;
        cout << "2. Random distribution of \"x\" living cells" << endl;
        cout << "3. Load configuration from a file" << endl;
        cin >> startMethod;
    } while (startMethod < 0 || startMethod > 4);


    if (startMethod == 1 || startMethod == 2) {
        cout << "Enter number of rows and cols for your game" << endl;
        cin >> rows >> cols;
        cout << "Game will start with the world of size: " << rows << "x" << cols << endl;
        cout << "Enter number starting cells: " << endl;
        cin >> count;
        game = new Game(rows, cols);

        if (startMethod == 1) {
            for (int i = 0; i < count; i++) {
                cout << "Cell (" << i + 1 << ") Enter the coordinates of cell: " << endl;
                cin >> x >> y;
                game->clearScreen();
                game->fillPosition(x, y);
                game->printGrid();
            }
        } else {
            game->fillRandomPositions(count);
        }

    } else {
        while (true) {
            cout << "Enter name of the file to read from: " << endl;
            cin >> filename;

            ifstream readfile(filename);
            if (readfile.is_open()) {
                string fileline, xx, yy;

                getline(readfile, fileline);
                stringstream ss(fileline);

                getline(ss, xx, ' ');
                getline(ss, yy, ' ');

                rows = stoi(xx);
                cols = stoi(yy);

                game = new Game(rows, cols);

                while (getline(readfile, fileline)) {
                    stringstream ss(fileline);

                    getline(ss, xx, ' ');
                    getline(ss, yy, ' ');

                    x = stoi(xx);
                    y = stoi(yy);

                    game->fillPosition(x, y);
                }
                break;
            } else {
                cout << "No such file, try again." << endl;
            }
        }
    }

    game->clearScreen();
    game->printGrid();
    cout << "Grid setup is done. Start the game ? (y/n)" << endl;
    cin >> confirm;

    if (confirm == "y" || confirm == "Y") {
        game->simulate(60); //TODO let user define it
    } else {
        game->clearScreen();
        return;
    }
}


