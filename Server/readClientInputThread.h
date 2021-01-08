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
    bool * terminate;
};

void *rcitFun(void *args) {
    rcitData * tempData = (rcitData *) args;
    int n = 0;
    char buffer[BUFFER_LEN];
    string message;

    rcitData data;
    data.connection = tempData->connection;

    while(true) {
        bzero(buffer, BUFFER_LEN);
        cout << "reading: " << data.connection->getId() << endl;
        n = read(data.connection->getSocket(), buffer, (BUFFER_LEN - 1));


        if (n <= 0 || *tempData->terminate) {
            if(n == 0) {
                cout << "Connection ended - deleting read thread" << endl;
            } else {
                perror("Error reading from socket");
                cout << "Connection terminated - deleting read thread" << endl;
            }
            data.connection->setTerminateConnection(true);
            pthread_cond_signal(&data.connection->getExecuteCond());
            return nullptr;
        }

        message = buffer;

        pthread_mutex_lock(&data.connection->getConnectionMediatorMut());
        data.connection->addAction(message);
        pthread_mutex_unlock(&data.connection->getConnectionMediatorMut());
        pthread_cond_signal(&data.connection->getExecuteCond());

    }
}

#undef BUFFER_LEN
#endif //SERVER_READINPUTTHREAD_H
