//
// Created by Eternal on 30/12/2020.
//

#ifndef SERVER_READINPUTTHREAD_H
#define SERVER_READINPUTTHREAD_H

#include <pthread.h>
#include <sys/socket.h>
#include <unistd.h>
#include <iostream>

#include "Connection.h"

#define BUFFER_LEN 10000

struct rcitData {
    Connection * connection;
};

void *rcitFun(void *args) {
    rcitData *data = (rcitData *) args;
    int n = 0;
    char buffer[BUFFER_LEN];
    string message;

    while(true) {
        bzero(buffer, BUFFER_LEN);
        n = read(data->connection->getSocket(), buffer, (BUFFER_LEN - 1));

        if (n < 0) {
            perror("Error reading from socket");
            return nullptr;
        }
        message = buffer;

        //TODO connection mutex lock
        //TODO connection add action
        //TODO connection signal processing thread
        //TODO on disconnect action kill thread
    }
//TODO nezabudnut zavriet klientske sockety
}

#undef BUFFER_LEN
#endif //SERVER_READINPUTTHREAD_H
