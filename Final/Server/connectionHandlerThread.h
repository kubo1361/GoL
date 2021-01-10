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
#include "readClientInputThread.h"
#include "processingThread.h"
#include <time.h>

struct chtData {
    int * serverSocket;
    bool * terminate;
    ServerStorage * storage;
    pthread_mutex_t * chtMut;
};

void *chtFun(void *args) {
    chtData *data = (chtData *) args;
    Connection *connection;
    int socket = 0;
    vector<Connection*> list;

    while (true) {
        pthread_mutex_lock(data->chtMut);
        connection = new Connection(time(0));
        list.push_back(connection);
        pthread_mutex_unlock(data->chtMut);


        cout << "Waiting for connection" << endl;
        socket = accept(*(data->serverSocket), (struct sockaddr *) &(connection->getClientAddress()),
                        &(connection->getClientAddressLength()));

        if(*data->terminate) {
            for (int i = 0; i < list.size(); ++i) {
                list[i]->shutdownSocket();
            }

            delete data->storage;
            delete connection;
            cout << "Deleting accept thread" << endl;
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
        dataRcit.terminate = data->terminate;
        dataPrt.connection = connection;
        dataPrt.terminate = data->terminate;
        dataPrt.chtMut = data->chtMut;

        pthread_create(&prThread, NULL, &prtFun, (void *)&dataPrt);
        pthread_detach(prThread);

        pthread_create(&rciThread, NULL, &rcitFun, (void *)&dataRcit);
        pthread_detach(rciThread);

        connection = nullptr;
    }
}


#endif //SERVER_CONNECTIONHANDLERTHREAD_H