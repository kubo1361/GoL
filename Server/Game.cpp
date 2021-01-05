//
// Created by Eternal on 22/12/2020.
//

#include "Game.h"
Game::Game(int dims) {
    srand(time(NULL));
    this->rows = dims;
    this->cols = dims;

    grid = new vector<vector<bool>>(rows, vector<bool>(cols, 0));
    secondaryGrid =  new vector<vector<bool>>(rows, vector<bool>(cols, 0));
}


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


/*
 * grid is primary. After calculation, new grid is stored as secondaryGrid.
 */
void Game::calculateState() {
    for (int x = 0; x < this->rows; x++) {
        for (int y = 0; y < this->cols; y++) {
            bool self = grid->at(x).at(y);
            int neighbors = countNeighbors(x, y);

            if ((self == false) && (neighbors == 3)) {
                secondaryGrid->at(x).at(y) = true;
            } else if ((self == true) && (neighbors < 2 || neighbors > 3)) {
                secondaryGrid->at(x).at(y) = false;
            } else {
                secondaryGrid->at(x).at(y) = self;
            }
        }
    }
    this->synchronizeGrids();
}


/*
 * Helper function for calculateState().
 */
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


/*
 * Synchronize grid according to secondaryGrid.
 */
void Game::synchronizeGrids() {
    for (int x = 0; x < this->rows; x++) {
        for (int y = 0; y < this->cols; y++) {
            grid->at(x).at(y) = secondaryGrid->at(x).at(y);
        }
    }
}


/*
 * Return living cells
 */
string Game::getState() {
    string size = to_string(this->rows) + ";" + to_string(this->cols);
    string livingCells = size + ";";
    string position = "";

    for (int x = 0; x < this->rows; x++) {
        for (int y = 0; y < this->cols; y++) {
            if (grid->at(x).at(y) == true) {
                position = to_string(x) + "." + to_string(y);
                livingCells += position + ",";
            }
        }
    }
    return livingCells; // x_size;y_size;5 2,6 8,4 6, ....
}


/*
 * Fills position at "x" and "y" with cell;
 */
void Game::fillPosition(int x, int y) {
    grid->at(x).at(y) = true;
}

/*
 * FIll positions according to arg
 */
void Game::fillPositions(string argFileCells) {
    vector<string> temp;
    stringstream  splitAction(argFileCells);
    string line;
    while(getline(splitAction,line,';'))
    {
        temp.push_back(line);
    }
    this->fillPositions(stoi(temp[0]),stoi(temp[1]),temp[2]);
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
            cout << line2 << endl;
            getline(splitCoordinates,line2,'.');
            coords[i] = stoi(line2);
        }
        this->fillPosition(coords[0], coords[1]);
    }
}

/*
 * Fills random "x" and "y" positions with cells;
 */
void Game::fillRandomPositions(int rows, int cols, int cellCount) {
    this->reshape(rows, cols);
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


/*
 * Change shape of grids.
 */
void Game::reshape(int x, int y) {
    this->rows = x;
    this->cols = y;
    this->restart();
}


/*
 * Restarts grids to blank state.
 */
void Game::restart() {
    delete this->grid;
    delete this->secondaryGrid;
    this->grid = new vector<vector<bool>>(rows, vector<bool>(cols, 0));
    this->secondaryGrid =  new vector<vector<bool>>(rows, vector<bool>(cols, 0));
}


/*
 * One step of a game.
 */
string Game::forwardStep() {
    this->calculateState();
    return this->getState();
}

string Game::backwardStep() {
    //TODO backward
    return "";
}




