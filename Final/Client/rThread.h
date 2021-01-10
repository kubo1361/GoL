//
// Created by janop on 30. 12. 2020.
//

#ifndef POS_SEM_RTHREAD_H
#define POS_SEM_RTHREAD_H

#include <cstring>
#define BUFFER_LEN 1000
struct rTData{
    Connection * con;
};

void * rThreadF(void* con) {

    rTData* connect = (rTData *)con;
    int n;
    char buffer[BUFFER_LEN];
    string action;
    string response;
    string action_raw;
    vector<string> action_full;
    string lastLoadedPattern;
    while(true) {


        pthread_mutex_lock(&(connect->con->getMut()));

        while (!connect->con->itHasAction()) {
            pthread_cond_wait(&connect->con->getCondR(), &connect->con->getMut());
        }



        action = connect->con->readAction();
        if(action.compare("end") == 0){
            return nullptr;
        }

        while(connect->con->getValid()) {

            sleep(1);
            n = write(connect->con->getSocketServer(), action.c_str(), action.length());

            if (n < 0) {
                perror("Error writing to socket");
                return nullptr;
            }

            bzero(buffer, BUFFER_LEN);
            n = read(connect->con->getSocketServer(), buffer, BUFFER_LEN - 1);


            if (n < 0) {
                perror("Error reading from socket");
                return nullptr;
            }

            string sprava = buffer;


            action_raw = sprava;


            stringstream splitAction(action_raw);
            string line;
            while (getline(splitAction, line, ';')) {
                action_full.push_back(line);
            }

            if(connect->con->getValid()){
            if (action_full[0].compare("loadPatternNames") ==0) { // action: loadPatternNames, return: name1;name2;name3;...

                cout << "Vyber subor ktory chces nacitat :" << endl;
                for(int i = 1; i < action_full.size(); i++)
                {
                    cout << i + " " + action_full.at(i) << endl;


                }
                cout << "Vyber subor ktory chces nacitat po vypise :" << endl;
                int poradie;
                cin >> poradie;
                action = "loadPattern;" + action_full.at(poradie);

                connect->con->getGame()->getName() = action_full.at(poradie);
                n = write(connect->con->getSocketServer(), action.c_str(), action.length());

                if (n < 0) {
                    perror("Error writing to socket");
                    return nullptr;
                }

                bzero(buffer, BUFFER_LEN);
                n = read(connect->con->getSocketServer(), buffer, BUFFER_LEN - 1);


                if (n < 0) {
                    perror("Error reading from socket");
                    return nullptr;
                }
                string sprava = buffer;


                action_raw = sprava;

                action_full.clear();
                stringstream splitAction(action_raw);
                string line;
                while (getline(splitAction, line, ';')) {
                    action_full.push_back(line);
                }


                if (action_full[0].compare("loadPattern") ==
                         0) { // action: loadPatternName;name, return: size_x;_size_y;livingCells
                    connect->con->getGame()->fillPositions(
                            stoi(action_full[1]),
                            stoi(action_full[2]),
                            action_full[3]);
                    connect->con->getGame()->clearScreen();
                    connect->con->getGame()->printGrid();
                    connect->con->getValid() = false;
                    connect->con->getReading() = true;

                }
            } else if (action_full[0].compare("randomPattern") ==
                       0) { // action: randomPattern;size_x;_size_y;count, return: size_x;_size_y;livingCells
                connect->con->getGame()->fillPositions(
                        stoi(action_full[1]),
                        stoi(action_full[2]),
                        action_full[3]);
                connect->con->getGame()->clearScreen();
                connect->con->getGame()->printGrid();
                connect->con->getValid() = false;
                connect->con->getReading() = true;


            } else if (action_full[0].compare("defineCells") ==
                       0) { // action: defineCells;size_x;_size_y;livingCells, return: Success
                connect->con->getGame()->fillPositions(
                        stoi(action_full[1]),
                        stoi(action_full[2]),
                        action_full[3]);
                connect->con->getGame()->clearScreen();
                connect->con->getGame()->printGrid();
                connect->con->getValid() = false;
                connect->con->getReading() = true;


            } else if (action_full[0].compare("forwardStep") ==
                       0) { // action: forwardStep, return: size_x;_size_y;livingCells
                if (action_full.size() <= 3) {
                    cout << "Hra skoncila" << endl;
                    cout << "Nacitaj hru zo servera alebo ukonci program" << endl;
                    connect->con->getValid() = false;
                    connect->con->getReading() = true;
                } else {
                connect->con->getGame()->fillPositions(
                        stoi(action_full[1]),
                        stoi(action_full[2]),
                        action_full[3]);
                connect->con->getGame()->clearScreen();
                connect->con->getGame()->printGrid();
                }

            } else if (action_full[0].compare("backwardStep") ==
                       0) { // action: backwardStep, return: size_x;_size_y;livingCells
                connect->con->getGame()->fillPositions(
                        stoi(action_full[1]),
                        stoi(action_full[2]),
                        action_full[3]);
                connect->con->getGame()->clearScreen();
                connect->con->getGame()->printGrid();



            } else if (action_full[0].compare("savePattern") == 0) { // action: savePattern;name, return: success
                cout << "Pattern Saved" << endl;

                connect->con->getValid() = false;

            } else if (action_full[0].compare("removePattern") == 0) { // action: savePattern;name, return: success
                cout << "Pattern Removed" << endl;
                connect->con->getValid() = false;

            }

            action_full.clear();
            connect->con->showMenu();
            }
        }
            pthread_mutex_unlock(&(connect->con->getMut()));

    }

}
#endif //POS_SEM_RTHREAD_H
