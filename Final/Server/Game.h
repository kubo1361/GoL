//
// Created by Eternal on 22/12/2020.
//
#include <iostream>
#include <unistd.h>
#include <stdlib.h>
#include <vector>
#include <sstream>

using namespace std;

#ifndef GOL_GAME_H
#define GOL_GAME_H

class Game {
private:
    int rows;
    int cols;

    vector<vector<bool>> * grid;
    vector<vector<bool>> * secondaryGrid;

public:
    Game(int dims);
    Game(int rows, int cols);
    ~Game();

    void fillPosition(int x, int y);
    void fillPositions(string argFileCells);
    void fillPositions(int rows, int cols, string argCells);
    void fillRandomPositions(int rows, int cols, int cellCount);

    void synchronizeGrids();
    void calculateState();
    int countNeighbors(int x, int y);

    void reshape(int x, int y);
    void restart();

    string getState();

    string forwardStep();
    string backwardStep();
};


#endif //GOL_GAME_H
