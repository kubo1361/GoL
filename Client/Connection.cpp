//
// Created by janop on 29. 12. 2020.
//

#include "Connection.h"

Connection::Connection() {


}



Connection::Connection(int id) {
    bzero(&this->address, sizeof(this->address));
    this->valid = true;
    pthread_mutex_init(&(this->mut), NULL);
    pthread_cond_init(&(this->condR), NULL);
    pthread_cond_init(&(this->condW), NULL);

    this->action = "";
    this->hasAction = false;

    this->game = nullptr;
    this->menu = new Menu();
}

Connection::~Connection() {


        shutdown(this->socket, SHUT_RDWR);
        close(this->socket);

    delete this->game;
    delete this->menu;
    pthread_cond_destroy(&(this->condR));
    pthread_cond_destroy(&(this->condW));
    pthread_mutex_destroy(&(this->mut));

}
void Connection::setGame(Game *g) {
    this->game = g;
}
Menu* Connection::getMenu() {
    return this->menu;
}
Game* Connection::getGame() {
    return this->game;
}

int& Connection::getSocketServer() {
    return this->socket;
}


sockaddr_in& Connection::getAddress() {
    return this->address;
}

socklen_t& Connection::getAddressLength() {
    return this->length;
}
pthread_t& Connection::getRThread() {
    return this->rThread;
}

pthread_mutex_t& Connection::getMut() {
    return this->mut;
}

pthread_cond_t& Connection::getCondR() {
    return this->condR;
}
pthread_cond_t& Connection::getCondW() {
    return this->condW;
}

bool &Connection::getValid() {
    return this->valid;
}
bool &Connection::getActiveCon() {
    return this->activeConnection;
}

string Connection::readAction() {
    this->hasAction = false;
    return this->action;
}

void Connection::writeAction(string response) {
    this->hasAction = true;
    this->action = response;
}

bool Connection::itHasAction() {
    return this->hasAction;
}

void Connection::showMenu() {
    cout << "1: Nacitaj hru" << endl;
    cout << "2: Krok dopredu" << endl;
    //cout << "3: Krok dozadu" << endl;
    cout << "3: Pauza" << endl;
    cout << "4: Pokracuj" << endl;
    cout << "5: Vymaz aktualnu hru zo serveru" << endl;
    cout << "6: Uloz" << endl;
    cout << "7: Nacitaj zo serveru" << endl;
    cout << "0: Koniec hry" << endl;
}
bool& Connection::getReading() {
    return this->reading;
}


