//
// Created by janop on 29. 12. 2020.
//

#ifndef CLIENT_CONNECTION_H
#define CLIENT_CONNECTION_H

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <strings.h>
#include <queue>
#include <pthread.h>
#include <iostream>
#include "Game.h"
#include "Menu.h"

using namespace std;

class Connection {
private:
    int socket;
    sockaddr_in address = sockaddr_in();
    bool valid = false;
    bool reading = true;
    socklen_t length = 0;
    bool activeConnection = true;
    Game* game;
    Menu* menu;


    pthread_t rThread;
    pthread_mutex_t mut;
    pthread_cond_t condR,condW;

    string action;
    bool hasAction;


public:

    Connection();
    Connection(int id);
    virtual ~Connection();

    void setGame(Game* g);
    Menu* getMenu();
    Game* getGame();
    void showMenu();

    bool& getReading();
    bool& getValid();
    bool& getActiveCon();
    int& getSocketServer();
    sockaddr_in& getAddress();
    socklen_t& getAddressLength();

    pthread_t& getRThread();
    pthread_mutex_t& getMut();
    pthread_cond_t& getCondR();
    pthread_cond_t& getCondW();

    string readAction();
    void writeAction(string response);
    bool itHasAction();

};

#endif //CLIENT_CONNECTION_H
