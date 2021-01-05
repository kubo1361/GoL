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


struct poTData{
    Connection * con;
};

void * pThreadF(void* connect) {

    poTData* con = (poTData *)connect;
    string action;
    string create =con->con->getMenu()->start();
    string message;
    string cmessage;
    string meno;
    bool pause = false;
    con->con->showMenu();
    while(true) {
        cin >> action;
        con->con->getValid() = false;
        switch (stoi(action)){
            case 1:
                message = create;
                break;
            case 2:
                message = "forwardStep";
                cmessage = message;
                pause = false;
                break;
            case 3:
                message ="backwardStep";
                cmessage = message;
                pause = false;
                break;
            case 4:
                pause = true;
                message = cmessage;

                break;
            case 5:
                pause = false;
                message = cmessage;
                con->con->getValid() = !pause;

                break;
            case 6:
                cout << "Nazov paternu "<< endl;
                cin >> meno;
                message= "savePattern;" + meno;
                break;
            case 7:
                message = "loadPatternNames;";
                pause = true;
                break;
            default :
                cout << "zle si zadal " << endl;
                break;

        }

        pthread_mutex_lock(&con->con->getMut());

        con->con->writeAction(message);

        /*cout << "WRITE uloz spravu: " << endl;
        cout << "WRITE uloz spravu: " << con->con->itHasAction() << endl;*/

        pthread_cond_signal(&con->con->getCondR());
        pthread_mutex_unlock(&con->con->getMut());

        con->con->getValid() = !pause;



    }

}
#endif //POS_SEM_PTHREAD_H
