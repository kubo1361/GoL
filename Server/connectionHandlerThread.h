//
// Created by Eternal on 30/12/2020.
//

#ifndef SERVER_CONNECTIONHANDLERTHREAD_H
#define SERVER_CONNECTIONHANDLERTHREAD_H

#include <pthread.h>
#include <sys/socket.h>
#include <unistd.h>
#include <iostream>

#include "ServerStorage.h"
#include "Connection.h"
#include "Clients.h"
#include "readClientInputThread.h"
#include "processingThread.h"
#include <time.h>

struct chtData {
    int * serverSocket;
    Clients * clients;
    ServerStorage * storage;
    pthread_mutex_t * chtMut;
};

void *chtFun(void *args) {
    chtData *data = (chtData *) args;
    Connection *connection;
    int socket = 0;

    while (true) {
        pthread_mutex_lock(data->chtMut);
        connection = data->clients->addConnection(time(0));
        pthread_mutex_unlock(data->chtMut);


        cout << "Waiting for connection" << endl;
        socket = accept(*(data->serverSocket), (struct sockaddr *) &(connection->getClientAddress()),
                        &(connection->getClientAddressLength()));

        if(data->clients->getTerminate()) {
            delete data->clients;
            delete data->storage;
            cout << "Deleting Clients" << endl;
            cout << "Deleting Storage" << endl;
            return nullptr;
        }

        pthread_mutex_lock(data->chtMut);
        if (socket < 0) {
            perror("Error creating client socket on accept");
            return nullptr;
        }
        connection->setSocket(socket);
        connection->connectStorage(data->storage);
        cout << "Connection estabilished: " << connection->getId() << endl;

        pthread_t rciThread, prThread;

        rcitData dataRcit;
        prtData dataPrt;
        dataRcit.connection = connection;
        dataPrt.connection = connection;
        dataPrt.clients = data->clients;

        pthread_create(&rciThread, NULL, &rcitFun, (void *)&dataRcit);
        pthread_create(&prThread, NULL, &prtFun, (void *)&dataPrt);

        pthread_detach(rciThread);
        pthread_detach(prThread);
        connection = nullptr;
        pthread_mutex_unlock(data->chtMut);
    }
}


#endif //SERVER_CONNECTIONHANDLERTHREAD_H