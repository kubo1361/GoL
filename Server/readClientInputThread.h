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

        pthread_mutex_lock(&data->connection->getConnectionMediatorMut());
        data->connection->addAction(message);
        pthread_mutex_unlock(&data->connection->getConnectionMediatorMut());

        pthread_cond_wait(&data->connection->getReadCond(), &data->connection->getConnectionMediatorMut());

        if(data->connection->isTerminatedConnection()) {
            return nullptr;
        }
    }
}

#undef BUFFER_LEN
#endif //SERVER_READINPUTTHREAD_H
