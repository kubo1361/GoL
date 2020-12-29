//
// Created by Eternal on 22/12/2020.
//

#include "Game.h"

Game::Game(int rows, int cols) {
    srand(time(NULL));
    this->rows = rows;
    this->cols = cols;

    grid = new vector<vector<bool>>(rows, vector<bool>(cols, 0));
    secondaryGrid =  new vector<vector<bool>>(rows, vector<bool>(cols, 0));
}

Game::~Game() {
    delete grid;
    delete secondaryGrid;
}

void Game::clearScreen() {
    system("clear");
    //cout << "\033[2J\033[1;1H";
}

void Game::calculateState() {
    for (int x = 0; x < this->rows; x++) {
        for (int y = 0; y < this->cols; y++) {
            bool self = grid->at(x).at(y);
            int neighbors = countNeighbors(x, y);

            if (self == false && neighbors == 3) {
                secondaryGrid->at(x).at(y) = true;
            } else if (self == true && (neighbors < 2 || neighbors > 3)) {
                secondaryGrid->at(x).at(y) = false;
            } else {
                secondaryGrid->at(x).at(y) = self;
            }
        }
    }
}

void Game::synchronizeGrids() {
    for (int x = 0; x < this->rows; x++) {
        for (int y = 0; y < this->cols; y++) {
            grid->at(x).at(y) = secondaryGrid->at(x).at(y);
    //*grid = *secondaryGrid;
        }
    }
}

int Game::countNeighbors(int x, int y) {
    int sum = 0;
    int posRow = 0;
    int posCol = 0;
    for (int i = -1; i < 2; ++i) {
        for (int j = -1; j < 2; ++j) {
            posRow = (x + i + this->rows) % this->rows;
            posCol = (y + j + this->cols) % this->cols;
            sum += grid->at(posRow).at(posCol);
        }
    }
    sum -= grid->at(x).at(y);
    return sum;
}

void Game::printGrid() {
    for (int x = 0; x < this->rows; x++) {
        for (int y = 0; y < this->cols; y++) {
            if (grid->at(x).at(y) == true) {
                cout << " O ";
            } else {
                cout << " . ";
            }
            if (y == cols - 1) {
                cout << endl;
            }
        }
    }
    cout << endl;
}

void Game::simulate(int fps) {
    while (true) {
        printGrid();
        calculateState();
        synchronizeGrids();
        sleep(1 / fps);
        clearScreen();
    }
}

void Game::fillPosition(int x, int y) {
    grid->at(x).at(y) = true;
}

void Game::fillRandomPositions(int cellCount) {
    int x;
    int y;
    while (cellCount > 0) {
        x = rand() % this->rows;
        y = rand() % this->cols;

        if (!(grid->at(x).at(y))) {
            grid->at(x).at(y) = true;
            cellCount--;
        }
    }
}
