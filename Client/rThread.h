//
// Created by janop on 30. 12. 2020.
//

#ifndef POS_SEM_RTHREAD_H
#define POS_SEM_RTHREAD_H

#include <cstring>

struct rTData{
    Connection * con;
};

void * rThreadF(void* con) {

    rTData* connect = (rTData *)con;
    int n;
    char buf[256];

    while(true) {
        printf("Cakam na  spravu\n");
        bzero(buf, 255);
        pthread_mutex_lock(&(connect->con->getMut()));
        while (connect->con->getQueueSize() > 0){
            pthread_cond_wait(&connect->con->getCondR(), &connect->con->getMut());
        }
        printf("Citam spravu\n");
        n = read(connect->con->getSocketServer(), buf, strlen(buf));
        if (n < 0) {
            perror("Error reading from socket");
            return nullptr;
        }
        string sprava = buf;
        cout << "sprava je : " << sprava << endl;
        pthread_mutex_lock(&(connect->con->getMut()));
        connect->con->addAction(buf);
        pthread_cond_signal(&(connect->con->getCondW()));
        pthread_mutex_unlock(&(connect->con->getMut()));

       /* while(connect->con->getQueueSize() > 0){
            pthread_cond_wait(&connect->con->getCondR(), &connect->con->getMut());
        }*/


    }

}
#endif //POS_SEM_RTHREAD_H
