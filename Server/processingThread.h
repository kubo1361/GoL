//
// Created by Eternal on 30/12/2020.
//

#ifndef SERVER_PROCESSINGTHREAD_H
#define SERVER_PROCESSINGTHREAD_H

#include <pthread.h>
#include <sys/socket.h>
#include <unistd.h>
#include <iostream>

#include "Connection.h"

struct prtData {
    Clients * clients;
    Connection * connection;
};

void * prtFun(void *args) {
    prtData *data = (prtData *) args;
    string action;

    while(true) {
        pthread_mutex_lock(&data->connection->getConnectionMediatorMut());

        while(data->connection->getNumberOfQueuedActions() == 0) {
            pthread_cond_wait(&data->connection->getExecuteCond(), &data->connection->getConnectionMediatorMut());
        }

        action = data->connection->getAction();

        //TODO API
        //if action = predefined action
        // execute method

        //TEST
        cout << "Received action is: " << action << endl;

        string response = "This is respone to action: " + action;

        write(data->connection->getSocket(), response.c_str(), response.length());
        ///////////////////////////////////////////////////

        pthread_mutex_unlock(&data->connection->getConnectionMediatorMut());

        if(data->connection->isTerminatedConnection()) {
            data->clients->removeConnection(data->connection->getId());
            return nullptr;
        }
    }

}

#endif //SERVER_PROCESSINGTHREAD_H
