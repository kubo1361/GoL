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
    Connection * connection;
};

void * prtFun(void *args) {
    prtData *data = (prtData *) args;

    while(true) {
        //TODO connection mutex lock
        //TODO while connection has no queued actions, cond wait for read thread
        //TODO choose queued action
        //TODO switch between functions according to action
        //TODO after execution, mutex unlock
        //TODO on disconnect action kill thread
    }

}

#endif //SERVER_PROCESSINGTHREAD_H
