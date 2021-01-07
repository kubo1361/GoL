//
// Created by janop on 5. 1. 2021.
//

#include "Game.h"

Game::Game(int dims) {
    srand(time(NULL));
    this->rows = dims;
    this->cols = dims;

    grid = new vector<vector<bool>>(rows, vector<bool>(cols, 0));
    //secondaryGrid =  new vector<vector<bool>>(rows, vector<bool>(cols, 0));
}


Game::Game(int rows, int cols) {
    srand(time(NULL));
    this->rows = rows;
    this->cols = cols;
    this->name = " ";
    grid = new vector<vector<bool>>(rows, vector<bool>(cols, 0));
    //secondaryGrid =  new vector<vector<bool>>(rows, vector<bool>(cols, 0));
}


Game::~Game() {
    delete grid;
    //delete secondaryGrid;
}


void Game::clearScreen() {
    system("clear");

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

void Game::simulate(int number) {
   /* while (true) {
        printGrid();
        calculateState();
        synchronizeGrids();
        sleep(1 / fps);
        clearScreen();
    }*/
}
void Game::fillPosition(int x, int y) {
    grid->at(x).at(y) = true;
}
/*
 * FIll positions according to arg
 */
void Game::fillPositions(int rows, int cols, string argCells) {
    this->reshape(rows, cols);
    string raw = argCells;
    stringstream  splitCells(raw);
    string line1;
    int coords[2];
    while(getline(splitCells,line1,','))
    {
        stringstream  splitCoordinates(line1);
        string line2;
        for (int i = 0; i < 2; ++i) {
          //  cout << line2 << endl;
            getline(splitCoordinates,line2,'.');
            coords[i] = stoi(line2);
        }
       // cout << "final: " << to_string(coords[0]) << " " << to_string(coords[1]) << endl;
        this->fillPosition(coords[0], coords[1]);
    }
}



/*
 * Change shape of grids.
 */
void Game::reshape(int x, int y) {
    this->rows = x;
    this->cols = y;
    this->restart();
}
void Game::restart() {
    delete this->grid;

    this->grid = new vector<vector<bool>>(rows, vector<bool>(cols, 0));

}
string& Game::getName() {
    return this->name;
}