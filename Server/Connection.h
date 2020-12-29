//
// Created by Eternal on 29/12/2020.
//

#ifndef SERVER_CONNECTION_H
#define SERVER_CONNECTION_H

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <strings.h>
#include <unistd.h>

using namespace std;

class Connection {
private:
    int socket;
    sockaddr_in clientAddress;
    socklen_t clientAddressLength;

    int n;
    char buffer[256];

public:
    Connection();
    ~Connection();




};


#endif //SERVER_CONNECTION_H

/*
   newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &cli_len); // acceptujem komunikaciu od klienta ?
   if (newsockfd < 0) {
       perror("ERROR on accept");
       return 3;
   }

   bzero(buffer, 256); // vynulujem buffer
   n = read(newsockfd, buffer, 255); // read cez socket, informacie do  buffera

   if (n < 0) {
       perror("Error reading from socket");
       return 4;
   }
   printf("Here is the message: %s\n", buffer);

   const char *msg = "I got your message";
   n = write(newsockfd, msg, strlen(msg) + 1); // zapis do socketu spravu o dlzke
   if (n < 0) {
       perror("Error writing to socket");
       return 5;
   }

   close(newsockfd); // zavri client socket
   close(sockfd);// zavri server socket
   */
