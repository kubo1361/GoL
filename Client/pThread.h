//
// Created by janop on 2. 1. 2021.
//

#ifndef POS_SEM_PTHREAD_H
#define POS_SEM_PTHREAD_H

#include "Connection.h"
#include <pthread.h>
#include <cstring>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <netdb.h>

#define BUFF 256

struct poTData{
    Connection * con;
};

void * pThreadF(void* connect) {

    poTData* con = (poTData *)connect;
    string action = "Nemam spravu";
    int  n;
    char buffer[BUFF];

    while(true) {
        n= 0;



        printf("Welcome in Game Of Life \n");
        printf("Napis co ta trapi na srdiecku \n");
        bzero(buffer,BUFF);
        fgets(buffer, 255, stdin);

        n = write(con->con->getSocketServer(), buffer, strlen(buffer));
        if (n < 0) {
            perror("Error writing to socket");
            return nullptr;
        }
        pthread_cond_broadcast(&con->con->getCondR());
        pthread_mutex_lock(&con->con->getMut());
        while(con->con->getQueueSize() == 0) {
            pthread_cond_wait(&con->con->getCondW(), &con->con->getMut());

        }


        action = con->con->getAction();
       //todo spracuj akciu

        cout << "Toto je kubova odpoved " << action << endl;
        pthread_cond_broadcast(&con->con->getCondR());
        pthread_mutex_unlock(&con->con->getMut());


    }

}
#endif //POS_SEM_PTHREAD_H
