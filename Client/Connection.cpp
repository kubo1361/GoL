//
// Created by janop on 29. 12. 2020.
//

#include "Connection.h"

Connection::Connection() {


}



Connection::Connection(int id) {

    this->id = id;
    bzero(&this->address, sizeof(this->address));
    this->valid = true;
    pthread_mutex_init(&(this->mut), NULL);
    pthread_cond_init(&(this->condR), NULL);
    pthread_cond_init(&(this->condW), NULL);

    this->actionBuf = new queue<string>();

}

Connection::~Connection() {

    if (this->valid) {
        shutdown(this->socket, SHUT_RD);
        close(this->socket);
    }


    delete this->actionBuf;
    pthread_cond_destroy(&(this->condR));
    pthread_cond_destroy(&(this->condW));
    pthread_mutex_destroy(&(this->mut));

}


int Connection::getId() {
    return this->id;
}

int& Connection::getSocketServer() {
    return this->socket;
}


sockaddr_in& Connection::getAddress() {
    return this->address;
}

socklen_t& Connection::getAddressLength() {
    return this->length;
}
pthread_t& Connection::getRThread() {
    return this->rThread;
}

pthread_mutex_t& Connection::getMut() {
    return this->mut;
}

pthread_cond_t& Connection::getCondR() {
    return this->condR;
}
pthread_cond_t& Connection::getCondW() {
    return this->condW;
}

bool &Connection::getValid() {
    return this->valid;
}
void Connection::addAction(string action) {
    this->actionBuf->push(action);
}
int Connection::getQueueSize() {
    return this->actionBuf->size();
}
string Connection::getAction() {
    if (actionBuf->empty()) {
        return "No more actions";
    } else {
        return  actionBuf->front();
    }
}
