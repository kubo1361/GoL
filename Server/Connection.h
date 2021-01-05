//
// Created by Eternal on 29/12/2020.
//

#ifndef SERVER_CONNECTION_H
#define SERVER_CONNECTION_H

#include <netinet/in.h>
#include <pthread.h>
#include <iostream>
#include <string.h>
#include <unistd.h>
#include <queue>

#include "Game.h"
#include "ServerStorage.h"

#define DEFAULT_DIM 10

using namespace std;

class Connection {
private:
    int id;

    int socket;
    sockaddr_in clientAddress;
    socklen_t clientAddressLength;

    pthread_mutex_t connectionMediatorMut;
    pthread_cond_t executeCond;

    queue<string> * actionBuffer;

    Game * game;
    ServerStorage * storage;

    bool terminatedConnection;

public:
    Connection(int arg);
    ~Connection();

    int getId();

    int getSocket();
    void setSocket(int arg);

    sockaddr_in & getClientAddress();

    socklen_t & getClientAddressLength();

    pthread_mutex_t &getConnectionMediatorMut();

    pthread_cond_t &getExecuteCond();

    bool isTerminatedConnection();
    void setTerminateConnection(bool arg);

    string getAction();
    void addAction(string arg);
    int getNumberOfQueuedActions();

    Game * getGame();
    ServerStorage * getStorage();
    void connectStorage(ServerStorage * arg);
};


#endif //SERVER_CONNECTION_H

/*


   const char *msg = "I got your message";
   n = write(newsockfd, msg, strlen(msg) + 1); // zapis do socketu spravu o dlzke
   if (n < 0) {
       perror("Error writing to socket");
       return 5;
   }

   close(newsockfd); // zavri Client socket
   close(sockfd);// zavri server socket
   */