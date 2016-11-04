#pragma once

#include <errno.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include "message.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <utility>
#include <vector>

using namespace std;

class Server {
public:
    Server(int port, bool isDebugging);
    ~Server();
    void run();
    
private:
    void create();
    void close_socket();
    void serve();
    void handle(int);
    string get_request(int);
    bool send_response(int, string);
    void get_value(int client, Message &message, string request);
    bool handle_message(int client, Message message, bool isSend);

    int port_;
    int server_;
    int buflen_;
    char* buf_;
    string cache;
    bool isDebug;
    map<string, vector<pair<string, string>>> messages;
};
