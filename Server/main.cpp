#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <iostream>
#include <curses.h>
#include <unistd.h>


using namespace std;

#define PORT 31313
#define HOST_COUNT 10

int main(int argc, char *argv[]) {

    sockaddr_in serverAddress;
    bzero((char *) &serverAddress, sizeof(serverAddress));
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = INADDR_ANY;
    serverAddress.sin_port = htons(PORT);

    int serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket < 0) {
        cerr << "Error creating socket" << endl;
        return 1;
    }

    if (bind(serverSocket, (struct sockaddr *) &serverAddress, sizeof(serverAddress)) < 0) {
        cerr << "Error binding socket address" << endl;
        return 2;
    }

    listen(serverSocket, 5);


    cout << "Press \"q\" to close" << endl;
    while (true) {
        /*
        char n = getch(); //TODO sfunkcni getch
        if (n == 113) {
            close(serverSocket);
            return 0;
        }
    }
         */
        return 0;
    }
}

#undef PORT
#undef HOST_COUNT