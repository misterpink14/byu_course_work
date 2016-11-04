#include "client.h"

Client::Client(string host, int port, bool isDebugging) {
    // setup variables
    host_ = host;
    port_ = port;
    buflen_ = 1024;
    buf_ = new char[buflen_+1];
    isDebug = isDebugging;
}

Client::~Client() {
}

void Client::run() {
    // connect to the server and run
    create();
    echo();
}

void
Client::create() {
    struct sockaddr_in server_addr;

    // use DNS to get IP address
    struct hostent *hostEntry;
    hostEntry = gethostbyname(host_.c_str());
    if (!hostEntry) {
        cout << "No such host name: " << host_ << endl;
        exit(-1);
    }

    // setup socket address structure
    memset(&server_addr,0,sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port_);
    memcpy(&server_addr.sin_addr, hostEntry->h_addr_list[0], hostEntry->h_length);

    // create socket
    server_ = socket(PF_INET,SOCK_STREAM,0);
    if (!server_) {
        perror("socket");
        exit(-1);
    }

    // connect to server
    if (connect(server_,(const struct sockaddr *)&server_addr,sizeof(server_addr)) < 0) {
        perror("connect");
        exit(-1);
    }
}

void
Client::close_socket() {
    close(server_);
}

void
Client::echo() {
    string command;
    // isLoop = true;
    
    // loop to handle user interface
    while (1) {
        cout << "% ";
        getline(cin,command);
        if (isDebug)
        {
            cout << "User entered : " << command << endl;
        }

        // parse command and send request
        bool success = parse_command(command);
        
        if (not success) // break if an error occurred
        {
            break;
        }
        // get a response
        success = get_response();
        
        if (not success) // break if an error occurred
        {
            break;
        }
    }
    close_socket();
}

bool
Client::parse_command(string command)
{
    string value;
    stringstream ss(command);
    stringstream ss2("");

    if (ss >> command)
    {
        if (command == "send") // put to server
        {
            ss2 << "put ";
            if (ss >> value)
            {
                ss2 << value << " ";
                if (ss >> value)
                {
                    ss2 << value << " ";
                    cout << "- Type your message. End with a blank line -" << endl;
                    string line, message = "";
                    bool isBlank = false;
                    while (getline(cin, line))
                    {
                        message += line;

                        if (line == "")
                            break;
                        else
                            message += "\n";
                    }
                    ss2 << message.length() << "\n" << message;
                }
                else
                {
                    return false;
                }
            }
            else
            {
                return false;
            }
        }
        else if (command == "list") // get list from server
        {
            ss2 << command << " ";
            if (ss >> value)
            {
                ss2 << value << '\n';
            }
            else
            {
                return false;
            }
        }
        else if (command == "read") // get one from server
        {
            ss2 << "get ";
            if (ss >> value)
            {
                ss2 << value << ' ';
                if (ss >> value)
                {
                    ss2 << value << '\n';
                }
                else
                {
                    return false;
                }
            }
            else
            {
                return false;
            }
        }
        else if (command == "quit") // quit
        {
            exit(1);
        }
        else if (command == "reset")
        {
            ss2 << "reset\n";
        }
        else // invalid
        {
            return false;
        }
    }
    else
    {
        return false;
    }
    if (isDebug)
    {
        cout << "User entered : " << ss.str();
    }
    return send_request(ss2.str());
}

bool
Client::send_request(string request) {
    // prepare to send request
    const char* ptr = request.c_str();
    int nleft = request.length();
    int nwritten;

    // loop to be sure it is all sent
    while (nleft) {
        if ((nwritten = send(server_, ptr, nleft, 0)) < 0) {
            if (errno == EINTR) {
                // the socket call was interrupted -- try again
                continue;
            } else {
                // an error occurred, so break out
                perror("write");
                return false;
            }
        } else if (nwritten == 0) {
            // the socket is closed
            return false;
        }
        nleft -= nwritten;
        ptr += nwritten;
    }
    if (isDebug)  
    {
        cout << "User send the following request : " << request << endl;
    }
    return true;
}

bool
Client::get_response() {
    string response = "";

    // read until we get a newline
    while (response.find("\n") == string::npos) {
        int nread = recv(server_,buf_,1024,0);
        
        if (nread < 0) {
            if (errno == EINTR) // the socket call was interrupted -- try again
            {
                continue;
            }
            else // an error occurred, so break out
            {
                return "";
            }
        } 
        else if (nread == 0) // the socket is closed
        {
            return "";
        }
        
        // be sure to use append in case we have binary data
        response.append(buf_,nread);
    }
    handle_response(response);
    return true;
}

void 
Client::handle_response(string response)
{
    if (response == "OK\n")
    {
        return;
    }

    // used for parsing
    stringstream ss(response);
    string value;
    ss >> value;
    
    if (value == "error" && isDebug)
    {
        cout << ss.str() << endl;
    }
    else if (value == "list")
    {
        if (ss >> value)
        {
            int i = 0;
            while(getline(ss, value))
            {
                if (value == "" && i == 0)
                    continue;
                cout << value << endl;
                i++;
            }
        }
    }
    else if (value == "message")
    {
        ss >> value;
        cout << value << endl;
        getline (ss, value);
        while (getline(ss, value))
        {
            cout << value << endl;
        }
    }
}