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
    string name;
    vector<vector<bool>> * grid;


public:
    Game(int dims);
    Game(int rows, int cols);
    ~Game();

    string& getName();
    void clearScreen();
    void printGrid();
    void fillPosition(int x, int y);

    void fillPositions(int rows, int cols, string argCells);





    void reshape(int x, int y);
    void restart();




};


#endif //PTHREAD_H_GAME_H
