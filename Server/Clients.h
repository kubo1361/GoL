//
// Created by Eternal on 29/12/2020.
//

#ifndef SERVER_CLIENTS_H
#define SERVER_CLIENTS_H

#include "Connection.h"
#include <vector>

class Clients {
private:
    vector<Connection*> connections;
    bool terminate;

public:
    Clients();
    ~Clients();

    Connection * addConnection(int arg);
    void removeConnection(int arg);

    bool getTerminate();
    void setTerminate(bool arg);
};


#endif //SERVER_CLIENTS_H
