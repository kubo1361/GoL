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
        if (con->con->getReading()) {
            cin >> action;
            con->con->getValid() = false;
            switch (stoi(action)) {
                case 0:
                    cout << "Program konci " << endl;
                    message = "end";
                    pthread_mutex_lock(&con->con->getMut());

                    con->con->writeAction(message);
                    pthread_cond_signal(&con->con->getCondR());
                    pthread_mutex_unlock(&con->con->getMut());

                    con->con->getActiveCon() = false;
                    return nullptr;
                case 1:
                    message = create;
                    con->con->getReading() = false;
                    break;
                case 2:
                    message = "forwardStep";
                    cmessage = message;
                    pause = false;
                    break;
                /*case 3:
                    message = "backwardStep";
                    cmessage = message;
                    pause = false;
                    break;*/
                case 3:
                    pause = true;
                    message = cmessage;

                    break;
                case 4:
                    pause = false;
                    message = cmessage;
                    con->con->getValid() = !pause;

                    break;
                case 5:
                    pause = false;
                    con->con->getGame()->getName();
                    if(con->con->getGame()->getName().compare(" ") != 0 ) {
                        message = "removePattern;" + con->con->getGame()->getName();
                    } else {
                        cout << "Nieje co zmazat, aktualna hra nie je ulozena na servery !" << endl;
                        pause = true;
                        message = "empty";
                        con->con->showMenu();
                    }

                    break;
                case 6:
                    pause = false;
                    cout << "Nazov paternu " << endl;
                    cin >> meno;
                    message = "savePattern;" + meno;
                    con->con->getGame()->getName() = meno;
                    break;

                case 7:
                    pause = false;
                    con->con->getReading() = false;
                    message = "loadPatternNames;";

                    break;
                default :
                    cout << "zle si zadal " << endl;
                    break;

            }

            pthread_mutex_lock(&con->con->getMut());

            con->con->writeAction(message);
            pthread_cond_signal(&con->con->getCondR());
            pthread_mutex_unlock(&con->con->getMut());

            con->con->getValid() = !pause;

        }

    }

}
#endif //POS_SEM_PTHREAD_H
