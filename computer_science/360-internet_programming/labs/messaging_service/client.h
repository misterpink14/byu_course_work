#pragma once

#include <errno.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>

#include <fstream>
#include <iostream>
#include <string>
#include <sstream>

using namespace std;

class Client {
public:
    Client(string host, int port, bool isDebugging);
    ~Client();
    void run();

private:
    virtual void create();
    virtual void close_socket();
    void echo();
    bool send_request(string);
    bool get_response();
    bool parse_command(string);
    void handle_response(string);

    string host_;
    int port_;
    int server_;
    int buflen_;
    char* buf_;
    bool isDebug;
};
