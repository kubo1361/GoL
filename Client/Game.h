//
// Created by janop on 5. 1. 2021.
//

#ifndef PTHREAD_H_GAME_H
#define PTHREAD_H_GAME_H
#include <iostream>
#include <unistd.h>
#include <stdlib.h>
#include <vector>
#include <sstream>

using namespace std;
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

    void clearScreen();
    void printGrid();
    void simulate(int number);
    void fillPosition(int x, int y);
    void fillPositions(string argFileCells);
    void fillPositions(int rows, int cols, string argCells);






    void reshape(int x, int y);
    void restart();

    //string getState();

    string forwardStep();
};


#endif //PTHREAD_H_GAME_H
