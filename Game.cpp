//
// Created by Eternal on 22/12/2020.
//

#include "Game.h"

Game::Game(int rows, int cols) {
    srand(time(NULL));
    this->rows = rows;
    this->cols = cols;

    grid = new structures::ArrayMatrix<bool>(rows, cols);
    secondaryGrid = new structures::ArrayMatrix<bool>(rows, cols);
}

Game::~Game() {
    delete grid;
    delete secondaryGrid;
}

void Game::clearScreen() {
    cout << "\033[2J\033[1;1H";
}

void Game::calculateState() {
    for (int x = 0; x < this->rows; x++) {
        for (int y = 0; y < this->cols; y++) {
            bool self = grid->get(x, y);
            int neighbors = countNeighbors(x, y);

            if (self == false && neighbors == 3) {
                secondaryGrid->set(x, y, true);
            } else if (self == true && (neighbors < 3 || neighbors > 3)) {
                secondaryGrid->set(x, y, false);
            } else {
                secondaryGrid->set(x, y, self);
            }
        }
    }
}

void Game::synchronizeGrids() {
    *grid = *secondaryGrid;
}

int Game::countNeighbors(int x, int y) {
    int sum = 0;
    int posRow = 0;
    int posCol = 0;
    for (int i = -1; i < 2; ++i) {
        for (int j = -1; j < 2; ++j) {
            posRow = (x + i + this->rows) % this->rows;
            posCol = (y + j + this->cols) % this->cols;
            sum += grid->get(posRow, posCol);
        }
    }
    sum -= grid->get(x, y);
    return sum;
}

void Game::printGrid() {
    for (int x = 0; x < this->rows; x++) {
        for (int y = 0; y < this->cols; y++) {
            if (secondaryGrid->get(x,y) == true) {
                cout << " O ";
            } else {
                cout << " . ";
            }
            if (y == cols - 1) {
                cout << endl;
            }
        }
    }
}

void Game::simulate(int fps) {
    while (true) {
        printGrid();
        calculateState();
        synchronizeGrids();
        sleep(fps / 1000);
        clearScreen();
    }
}

void Game::fillPosition(int x, int y) {
    grid->set(x, y, true);
}

void Game::fillRandomPositions(int cellCount) {
    int x;
    int y;
    while (cellCount > 0) {
        x = rand() % this->rows;
        y = rand() % this->cols;

        if (!(grid->get(x, y))) {
            grid->set(x, y, true);
            cellCount--;
        }
    }
}
