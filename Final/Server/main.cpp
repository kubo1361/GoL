#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <iostream>
#include <curses.h>
#include <unistd.h>

#include "connectionHandlerThread.h"


using namespace std;

#define PORT 31313
#define HOST_COUNT 10

int main(int argc, char *argv[]) {
    cout << "Starting server" << endl;

    sockaddr_in serverAddress;
    bzero((char *) &serverAddress, sizeof(serverAddress));
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = INADDR_ANY;
    serverAddress.sin_port = htons(PORT);

    cout << "Creating socket" << endl;
    int serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket < 0) {
        cerr << "Error creating server socket" << endl;
        return 1;
    }

    cout << "Binding socket address" << endl;
    if (bind(serverSocket, (struct sockaddr *) &serverAddress, sizeof(serverAddress)) < 0) {
        cerr << "Error binding socket address" << endl;
        return 2;
    }

    listen(serverSocket, HOST_COUNT);

    bool terminateAccept = false;
    ServerStorage * storage = new ServerStorage();
    pthread_t chThread;
    pthread_mutex_t chtMut = PTHREAD_MUTEX_INITIALIZER;

    chtData data;
    data.serverSocket = &serverSocket;
    data.terminate = &terminateAccept;
    data.storage = storage;
    data.chtMut = &chtMut;

    pthread_create(&chThread, NULL, &chtFun, (void *)&data);
    pthread_detach(chThread);

    sleep(1);
    cout << "Press \"q\" to close" << endl;
    initscr();
    raw();
    noecho();
    cbreak();

    while (true) {
        char n = getch();
        if (n == 113) {
            cout << "Shutting down server" << endl;
            terminateAccept = true;
            pthread_mutex_destroy(&chtMut);
            shutdown(serverSocket, SHUT_RDWR);
            close(serverSocket);
            endwin();
            sleep(5);
            return 0;
        }
    }
}
#undef PORT
#undef HOST_COUNT