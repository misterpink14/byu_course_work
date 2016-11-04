#include <stdlib.h>
#include <unistd.h>

#include <iostream>

#include "server.h"

using namespace std;

int
main(int argc, char **argv)
{
    int option, port;

    // setup default arguments
    port = 3000;

    bool isDebugging = false;

    // process command line options using getopt()
    // see "man 3 getopt"
    while ((option = getopt(argc,argv,"p:")) != -1) {
        switch (option) {
            case 'p':
                port = atoi(optarg);
                break;
            case 'd':
                isDebugging = true;
            default:
                cout << "server [-p port]" << endl;
                exit(EXIT_FAILURE);
        }
    }

    Server server = Server(port, isDebugging);
    server.run();
}
