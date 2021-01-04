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

using namespace std;

class Connection {
private:

    int id;
    int socket;
    sockaddr_in address = sockaddr_in();
    bool valid = false;
    socklen_t length = 0;

    pthread_t rThread;
    pthread_mutex_t mut;
    pthread_cond_t condR,condW;


    queue<string> * actionBuf;


public:

    Connection();
    Connection(int id);
    virtual ~Connection();

    bool& getValid();
    int getId();
    int& getSocketServer();
    sockaddr_in& getAddress();
    socklen_t& getAddressLength();

    pthread_t& getRThread();
    pthread_mutex_t& getMut();
    pthread_cond_t& getCondR();
    pthread_cond_t& getCondW();
    void addAction(string arg);
    int getQueueSize();
    string getAction();

};

#endif //CLIENT_CONNECTION_H
