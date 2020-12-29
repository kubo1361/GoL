//
// Created by janop on 29. 12. 2020.
//

#include "Connection.h"

Connection::Connection() {

    bzero(&this->address, sizeof(this->address));

    pthread_mutex_init(&(this->mut), NULL);
    pthread_cond_init(&(this->cond), NULL);

}



Connection::Connection(int id) {

    this->id = id;
    bzero(&this->address, sizeof(this->address));

    pthread_mutex_init(&(this->mut), NULL);
    pthread_cond_init(&(this->cond), NULL);

}

Connection::~Connection() {

    if (this->valid) {
        shutdown(this->socket, SHUT_RD);
        close(this->socket);
    }



    pthread_cond_destroy(&(this->cond));
    pthread_mutex_destroy(&(this->mut));

}


int Connection::getId() {
    return this->id;
}

int& Connection::getSocketServer() {
    return this->socket;
}

sockaddr_in& Connection::getAddr() {
    return this->address;
}

socklen_t& Connection::getAddressLength() {
    return this->length;
}

pthread_mutex_t& Connection::getMut() {
    return this->mut;
}

pthread_cond_t& Connection::getCond() {
    return this->cond;
}

bool &Connection::getValid() {
    return this->valid;
}



