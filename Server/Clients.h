//
// Created by Eternal on 29/12/2020.
//

#ifndef SERVER_CLIENTS_H
#define SERVER_CLIENTS_H

#include "Connection.h"
#include <unordered_map>

class Clients {
private:
    unordered_map<int, Connection*> connections;
public:
    Clients();
    ~Clients();

    Connection * addConnection();
};


#endif //SERVER_CLIENTS_H
