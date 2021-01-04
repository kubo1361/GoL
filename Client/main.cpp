#include "Connection.h"
#include "rThread.h"
#include "pThread.h"
#include <pthread.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <netdb.h>
#include <curses.h>

#define PORT 31313
#define BUFF 256
int main (int argc, char* argv[]){
    Connection* con = new Connection(15);
    struct hostent* serv = gethostbyname("frios2.fri.uniza.sk");

    if (serv == NULL) {
        delete con;
        con = nullptr;
        fprintf( stderr,"Server nieje dostupny\n");
        return 2;
    }

    char buffer[BUFF];

    bzero((char*)&(con->getAddress()), sizeof(con->getAddress()));
    con->getAddress().sin_family = AF_INET;

    bcopy(
            (char*)serv->h_addr,
            (char*)&(con->getAddress()).sin_addr.s_addr,
            serv->h_length
    );

    con->getAddress().sin_port = htons(PORT);
    con->getSocketServer() = socket(AF_INET, SOCK_STREAM, 0);

    if(con->getSocketServer() < 0){
        perror("Nastala chyba pri vytvoreni socketu");
        return 3;
    }
    if(connect(con->getSocketServer(), (struct sockaddr*)&con->getAddress(), sizeof(con->getAddress())) < 0)
    {
        perror("Error connecting to socket");
        return 4;
    }
    pthread_t rThread;
    pthread_t prThread;
    pthread_mutex_lock(&con->getMut());

    poTData dataa;
    dataa.con = con;
    pthread_create(&prThread, NULL, &pThreadF, (void*) &dataa);
    pthread_detach(prThread);

    rTData data;
    data.con = con;
    pthread_create(&rThread, NULL, &rThreadF, (void*) &data);
    pthread_detach(rThread);
    pthread_mutex_unlock(&con->getMut());
    sleep(1);
    cout << "Press \"q\"to close" << endl;
    initscr();
    raw();
    noecho();
    cbreak();

    while (true) {
        char n = getch();
        if (n == 113) {
            close(con->getSocketServer());

            endwin();
            sleep(1);
            cout << "Shutting down client" << endl;
            return 0;
        }
    }

}