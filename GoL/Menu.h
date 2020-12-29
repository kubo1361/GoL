//
// Created by Eternal on 22/12/2020.
//
#include <iostream>
#include <fstream>
#include <sstream>
#include "Game.h"

using namespace std;

#ifndef GOL_MENU_H
#define GOL_MENU_H


class Menu {
private:
    Game * game = nullptr;

public:
    Menu();
    ~Menu();

    void start();
};


#endif //GOL_MENU_H
