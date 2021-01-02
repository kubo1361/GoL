//
// Created by Eternal on 29/12/2020.
//

#include "Clients.h"

Clients::Clients() {
    this->terminate = false;
}

Clients::~Clients() {
    for(int i = 0; i < connections.size(); i++) {
        delete connections[i];
    }
}

Connection * Clients::addConnection(int arg) {
    this->connections.push_back(new Connection(arg));
    return this->connections.back();
}

void Clients::removeConnection(int arg) {
    Connection * temp;
    for (int i = 0; i < connections.size(); ++i) {
        if(connections[i]->getId() == arg) {
            temp = connections[i];
            connections.erase(connections.begin() + i);
        }
        delete temp;
    }
}

bool Clients::getTerminate() {
    return this->terminate;
}

void Clients::setTerminate(bool arg) {
    this->terminate = arg;
}
