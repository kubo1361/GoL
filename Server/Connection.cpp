//
// Created by Eternal on 29/12/2020.
//

#include "Connection.h"

Connection::Connection() {
    this->clientAddressLength = sizeof(clientAddress);
    bzero(&this->clientAddress, this->clientAddressLength);

    this->actionBuffer = new queue<string>();

    pthread_mutex_init(&(this->connectionMediatorMut), NULL);
    pthread_cond_init(&(this->readCond), NULL);
    pthread_cond_init(&(this->executeCond), NULL);

    this->terminatedConnection = false;
}

Connection::~Connection() {
    delete actionBuffer;

    pthread_mutex_destroy(&(this->connectionMediatorMut));
    pthread_cond_destroy(&(this->readCond));
    pthread_cond_destroy(&(this->executeCond));
}

int Connection::getSocket() {
    return this->socket;
}

void Connection::setSocket(int arg) {
    this->socket = arg;
}

sockaddr_in & Connection::getClientAddress() {
    return this->clientAddress;
}

socklen_t & Connection::getClientAddressLength() {
    return this->clientAddressLength;
}

pthread_mutex_t& Connection::getConnectionMediatorMut() {
    return this->connectionMediatorMut;
}

pthread_cond_t &Connection::getReadCond() {
    return this->readCond;
}

pthread_cond_t &Connection::getExecuteCond() {
    return this->executeCond;
}

bool Connection::isTerminatedConnection() {
    return this->terminatedConnection;
}

void Connection::setTerminateConnection(bool arg) {
    this->terminatedConnection = arg;
}

string Connection::getAction() {
    if(actionBuffer->empty()) {
        return "empty";
    } else {
        return actionBuffer->front();
    }

}

void Connection::addAction(string arg) {
    this->actionBuffer->push(arg);
}
