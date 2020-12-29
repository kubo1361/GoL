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

#include <iostream>

using namespace std;

class Connection {
private:

    int id;
    int socket = 0;
    sockaddr_in address = sockaddr_in();
    bool valid = false;
    socklen_t length = 0;

    pthread_mutex_t mut;
    pthread_cond_t cond;


public:

    Connection();
    Connection(int id);
    virtual ~Connection();

    bool& getValid();
    int getId();
    int& getSocketServer();
    sockaddr_in& getAddr();
    socklen_t& getAddressLength();

    pthread_mutex_t& getMut();
    pthread_cond_t& getCond();

};

#endif //CLIENT_CONNECTION_H
