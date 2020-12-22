//
// Created by Eternal on 22/12/2020.
//
#include <iostream>
#include <unistd.h>
#include <stdlib.h>
#include "structures/ArrayMatrix.h"

using namespace std;

#ifndef GOL_GAME_H
#define GOL_GAME_H

class Game {
private:
    int rows;
    int cols;

    structures::ArrayMatrix<bool>* grid;
    structures::ArrayMatrix<bool>* secondaryGrid;

public:
    Game(int rows, int cols);
    ~Game();

    void printGrid();
    void synchronizeGrids();
    void calculateState();
    int countNeighbors(int x, int y);
    void clearScreen();
    void fillPosition(int x, int y);
    void fillRandomPositions(int cellCount);

    void simulate(int fps);
};


#endif //GOL_GAME_H
