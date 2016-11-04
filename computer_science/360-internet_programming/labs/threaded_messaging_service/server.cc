#include "server.h"

Server::Server(int port, bool isDebugging) {
	// setup variables
	port_ = port;
	buflen_ = 1024;
	buf_ = new char[buflen_+1];
	cache = "";
	isDebug = isDebugging;

	// Initialize sepaphores
	sem_init(&sem_, 0, 1);
	sem_init(&sem_cache_, 0, 1);
}

Server::~Server() {
	delete buf_;
}

void
Server::run() {
	// create and run the server
	create();
	serve();
}

void
Server::create() {
	struct sockaddr_in server_addr;

	// setup socket address structure
	memset(&server_addr,0,sizeof(server_addr));
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(port_);
	server_addr.sin_addr.s_addr = INADDR_ANY;

	// create socket
	server_ = socket(PF_INET,SOCK_STREAM,0);
	if (!server_) {
		perror("socket");
		exit(-1);
	}

	// set socket to immediately reuse port when the application closes
	int reuse = 1;
	if (setsockopt(server_, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse)) < 0) {
		perror("setsockopt");
		exit(-1);
	}

	// call bind to associate the socket with our local address and
	// port
	if (::bind(server_,(const struct sockaddr *)&server_addr,sizeof(server_addr)) < 0) {
		perror("bind");
		exit(-1);
	}

	// convert the socket to listen for incoming connections
	if (listen(server_,SOMAXCONN) < 0) {
		perror("listen");
		exit(-1);
	}
}

void
Server::close_socket() 
{
	close(server_);
}

void
Server::serve() 
{
	int i = 10;
	while (i-- > 0) // Create thread pool
	{
		pthread_t th;
		pthread_create(&th, NULL, &handle_client, this);
	}

	master();
	close_socket();
}

bool
Server::handle(int client) 
{
	// handle one request at a time
	// get a request
	string request;
	if (cache == "")
	{
		request = get_request(client);
	}
	else 
	{
		request = cache;
		cache = "";
	}
	if (isDebug)
	{
		cout << "Received " << request << endl;
	}

	// return false if client is done or an error occurred
	if (request.empty())
	{
		if (isDebug)
		{
			cout << "Received empty request" << endl;
		}
		return false;
	}

	// Used for parsing
	stringstream iss(request);
	
	// parse response
	Message message(iss);

	if (isDebug)
	{
		cout << "First line of the request has been processed " << endl;
	}

	request = iss.str();
	if (request != "")
	{
		cache = request;
	}
	
	// get more characters if needed
	if (message.isNeeded)
	{
		if (isDebug)
		{
			cout << "More is needed from the request " << endl;
		}
		bool success = true;

		if (!success) // close the client
		{
			return false;
		}

		string req;
		if (cache == "")
		{
			req = get_request (client);
		}
		else 
		{
			req = cache;
		}
		
		int len = stoi(message.params.at(2)); // cast the length to an int
		while (len > req.length())	// Get more data
		{
			req += get_request (client);
		}

		message.value = req.substr (0, len);
					
		cache = req.substr (len, req.length()-1);
	}

	if (isDebug)
	{
		cout << "The request has been processed " << endl;
	}

	bool success = handle_message(client, message, true); 
	if (isDebug)
	{
		cout << "After handle_message " << endl;
	}
	// break if an error occurred
	if (!success)
	{
		return false;
	}

	return true;
}

bool
Server::handle_message(int client, Message message, bool isSend) { 

	if (isDebug)
	{
		cout << "The request is being handled " << endl;
	}
	string msg;

	// put values into storage
	if (message.command == "put")
	{
		pair<string, string> p (message.params.at(1), message.value);
		map<string, vector<pair<string, string>>>::iterator it = messages.find(message.params[0]);
		if (it != messages.end())
		{
			it->second.push_back(p);
		}
		else
		{
			vector <pair<string, string>> v;
			v.push_back(p);
			messages.insert(pair<string, vector<pair<string, string>>>(message.params.at(0), v));
		}
		msg = "OK\n";
	}
	else if (message.command == "list") // get all from name
	{
		map<string, vector<pair<string, string>>>::iterator it = messages.find(message.params[0]);
		if (it == messages.end())
		{
			msg = "error " + message.params.at(0) + " does not exist\n";
		}
		else
		{
			msg = "list " + to_string(it->second.size()) + "\n";
			for (unsigned i = 0; i < it->second.size(); i++)
			{
				msg += to_string(i+1) + " " + it->second[i].first;
				msg+="\n";
			}
		}
	}
	else if (message.command == "get") // get a single entry
	{
		map<string, vector<pair<string, string>>>::iterator it = messages.find(message.params[0]);
		if (it == messages.end())
		{
			msg = "error " + message.params.at(0) + " does not exist\n";
		}
		else
		{
			msg = "message ";
			int i = stoi(message.params.at(1));
			i--;
			msg += it->second[i].first + " " + to_string(it->second[i].second.length()) + "\n" + it->second[i].second;
		}
	}
	else if (message.command == "reset") // reset the storage
	{
		messages.clear();
		msg = "OK\n";
	}
	else // invalid
	{
		msg = "error invalid request\n";
	}
	if (isSend == false && message.command != "error")
	{
		return true;
	}

	if (isDebug)
	{
		cout << "Sending\n*******\n" << msg << "\n*******\n";
	}
	return send_response(client, msg);
}

string
Server::get_request(int client) {
	string request = "";

	// Read everything
	int nread;
	while ((nread = recv(client,buf_,1024,0)) > 0) {
		if (nread < 0) {
			if (errno == EINTR) // the socket call was interrupted -- try again
			{
				if (isDebug)
					perror("the socket was interrupted");
				continue;
			}
			else // an error occurred, so break out
			{ 
				if (isDebug)
					perror("an error occurred");
				return "";
			}
		} else if (nread == 0) { // the socket is closed
			if (isDebug)
				perror("the socket is closed");
			return "";
		}
		// be sure to use append in case we have binary data
		request.append(buf_,nread);
		if (nread < 1024)
		{
			break;
		}
	}

	if (isDebug)
	{
		cout << "---------\nGOT => " + request + "\n----------\n";
	}
	return request;
}

bool
Server::send_response(int client, string response) 
{
	// prepare to send response
	const char* ptr = response.c_str();
	int nleft = response.length();
	int nwritten;

	// loop to be sure it is all sent
	while (nleft) {
		if ((nwritten = send(client, ptr, nleft, 0)) < 0) {
			
			if (errno == EINTR) {
				// the socket call was interrupted -- try again
				continue;
			} else {
				// an error occurred, so break out
				return false;
			}
		} else if (nwritten == 0) {
			// the socket is closed
			return false;
		}
		
		nleft -= nwritten;
		ptr += nwritten;
	}
	return true;
}

void
Server::master()
{
    int client;
    struct sockaddr_in client_addr;
    while (true) {
	    socklen_t clientlen = sizeof(client_addr);
        if ((client = accept(server_,(struct sockaddr *)&client_addr,&clientlen)) > 0)
        {
            q.push(client);
        }
    }
    close_socket();
}

void *
handle_client(void* vptr)
{
    Server* serv = (Server*) vptr;
    while (true)
    {
        int client = serv->q.pop();
        sem_wait(&serv->sem_);
        bool isSending = serv->handle(client);
        sem_post(&serv->sem_);
        if (isSending) // Wait for the client to close the connection before we do
        {
	        serv->q.push(client);
        }
    }
}
