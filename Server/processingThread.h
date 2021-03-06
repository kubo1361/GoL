//
// Created by Eternal on 30/12/2020.
//

#ifndef SERVER_PROCESSINGTHREAD_H
#define SERVER_PROCESSINGTHREAD_H

#include <pthread.h>
#include <sys/socket.h>
#include <unistd.h>
#include <iostream>
#include <sstream>
#include <stdlib.h>

#include "Connection.h"

struct prtData {
    bool * terminate;
    Connection *connection;
    pthread_mutex_t * chtMut;
};

void *prtFun(void *args) {
    prtData *tempData = (prtData *) args;
    string action_raw;
    string temp;
    vector<string> action_full;

    prtData data;
    data.connection = tempData->connection;
    pthread_mutex_unlock(tempData->chtMut);

    while (true) {
        pthread_mutex_lock(&data.connection->getConnectionMediatorMut());

        while (data.connection->getNumberOfQueuedActions() == 0) {
            pthread_cond_wait(&data.connection->getExecuteCond(), &data.connection->getConnectionMediatorMut());
            if (data.connection->isTerminatedConnection() || *tempData->terminate) {
                pthread_mutex_unlock(&data.connection->getConnectionMediatorMut());
                delete data.connection;
                cout << "Connection ended - deleting processing thread" << endl;
                return nullptr;
            }
        }
        cout << "proccessing: id: " << data.connection->getId() << " socket: " << data.connection->getSocket()
             << endl;
        pthread_mutex_unlock(&data.connection->getConnectionMediatorMut());

        action_raw = data.connection->getAction();
        stringstream splitAction(action_raw);
        string line;

        cout << "action: " << action_raw << endl;

        while (getline(splitAction, line, ';')) {
            action_full.push_back(line);
        }


        if (action_full[0].compare("loadPatternNames") == 0) {
            // action: loadPatternNames, return: name1;name2;name3;...
            temp = "loadPatternNames" + data.connection->getStorage()->getPatternNames();
            cout << temp << endl;
        } else if (action_full[0].compare("loadPattern") == 0) {
            // action: loadPatternName;name, return: size_x;_size_y;livingCells
            temp = data.connection->getStorage()->getPattern(action_full[1]);
            data.connection->getGame()->fillPositions(temp);
            temp = "loadPattern;" + data.connection->getGame()->getState();
            cout << temp << endl;
        } else if (action_full[0].compare("removePattern") == 0) {
            // action: removePattern;name, return: removePattern
            data.connection->getStorage()->removePattern(action_full[1]);
            temp = "removePattern";
            cout << temp << endl;
        } else if (action_full[0].compare("randomPattern") == 0) {
            // action: randomPattern;size_x;_size_y;count, return: size_x;_size_y;livingCells
            data.connection->getGame()->fillRandomPositions(
                    stoi(action_full[1]),
                    stoi(action_full[2]),
                    stoi(action_full[3]));

            temp = "randomPattern;" + data.connection->getGame()->getState();
            cout << temp << endl;
        } else if (action_full[0].compare("defineCells") == 0) {
            // action: defineCells;size_x;_size_y;livingCells, return: defineCells;size_x;_size_y;livingCells
            data.connection->getGame()->fillPositions(

                    stoi(action_full[1]),
                    stoi(action_full[2]),
                    action_full[3]);
            temp = "defineCells;" + data.connection->getGame()->getState();
            cout << temp << endl;

        } else if (action_full[0].compare("forwardStep") == 0) {
            // action: forwardStep, return: size_x;_size_y;livingCells
            temp = "forwardStep;" + data.connection->getGame()->forwardStep();
            cout << temp << endl;
        } else if (action_full[0].compare("backwardStep") == 0) {
            // action: backwardStep, return: size_x;_size_y;livingCells
            temp = "backwardStep;" + data.connection->getGame()->backwardStep();
            cout << temp << endl;
        } else if (action_full[0].compare("savePattern") == 0) {
            // action: savePattern;name, return: savePattern
            temp = data.connection->getGame()->getState();
            cout << "savePattern: " << temp << endl;
            data.connection->getStorage()->addPattern(action_full[1], temp);
            temp = "savePattern";
            cout << temp << endl;
        }
        pthread_mutex_lock(&data.connection->getConnectionMediatorMut());
        write(data.connection->getSocket(), temp.c_str(), temp.length());
        action_full.clear();
        temp.clear();
        pthread_mutex_unlock(&data.connection->getConnectionMediatorMut());
    }
}

#endif //SERVER_PROCESSINGTHREAD_H
