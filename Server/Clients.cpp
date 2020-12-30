//
// Created by Eternal on 29/12/2020.
//

#include "Clients.h"

Clients::Clients() {

}

Clients::~Clients() {
    for(int i = 0; i < connections.size(); i++) {
        delete connections[i];
    }
}

Connection * Clients::addConnection() {
    this->connections.push_back(new Connection());
    return this->connections.back();
}