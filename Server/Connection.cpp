//
// Created by Eternal on 29/12/2020.
//

#include "Connection.h"

Connection::Connection(int arg) {
    this->id = arg;
    this->clientAddressLength = 0;
    bzero(&this->clientAddress, sizeof(clientAddress));

    this->actionBuffer = new queue<string>();

    pthread_mutex_init(&(this->connectionMediatorMut), NULL);
    pthread_cond_init(&(this->executeCond), NULL);

    this->terminatedConnection = false;

    this->game = new Game(DEFAULT_DIM);
    this->storage = nullptr;

    this->hasSocket = false;
}

Connection::~Connection() {
    delete actionBuffer;

    if(this->hasSocket) {
        shutdown(this->socket, SHUT_RD);
    }

    pthread_mutex_destroy(&(this->connectionMediatorMut));
    pthread_cond_destroy(&(this->executeCond));
    close(this->socket);

    delete game;
}

int Connection::getSocket() {
    return this->socket;
}

void Connection::setSocket(int arg) {
    this->hasSocket = true;
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
        string temp = actionBuffer->front();
        actionBuffer->pop();
        return temp;
    }

}

void Connection::addAction(string arg) {
    this->actionBuffer->push(arg);
}

int Connection::getNumberOfQueuedActions() {
    return this->actionBuffer->size();
}

int Connection::getId() {
    return this->id;
}

Game *Connection::getGame() {
    return this->game;
}

ServerStorage *Connection::getStorage() {
    return this->storage;
}

void Connection::connectStorage(ServerStorage * arg) {
    this->storage = arg;
}

void Connection::shutdownSocket() {
    this->hasSocket = false;
    shutdown(this->socket, SHUT_RD);
}

#undef DEFAULT_DIM