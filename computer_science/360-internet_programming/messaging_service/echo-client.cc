#include <stdlib.h>
#include <unistd.h>

#include <iostream>

#include "client.h"

using namespace std;

int
main(int argc, char **argv)
{
    int option;

    // setup default arguments
    int port = 5000;
    string host = "localhost";
    bool isDebugging = false;

    // process command line options using getopt()
    // see "man 3 getopt"
    while ((option = getopt(argc,argv,"h:p:d")) != -1) {
        switch (option) {
            case 'p':
                port = atoi(optarg);
                break;
            case 'h':
                host = optarg;
                break;
            case 'd':
                isDebugging = true;
                break;
            default:
                cout << "client [-h host] [-p port] [-d]" << endl;
                exit(EXIT_FAILURE);
        }
    }

    Client client = Client(host, port, isDebugging);
    client.run();
}

