#include "server.h"

Server::Server(int port, bool isDebugging) {
	// setup variables
	port_ = port;
	buflen_ = 1024;
	buf_ = new char[buflen_+1];
	cache = "";
	isDebug = isDebugging;
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
Server::close_socket() {
	close(server_);
}

void
Server::serve() {
	// setup client
	int client;
	struct sockaddr_in client_addr;
	socklen_t clientlen = sizeof(client_addr);

	  // accept clients
	while ((client = accept(server_,(struct sockaddr *)&client_addr,&clientlen)) > 0) {

		handle(client);
	}
	close_socket();
}

void
Server::handle(int client) {

	// loop to handle all requests
	while (1) {
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
		// break if client is done or an error occurred
		if (request.empty())
		{
			if (isDebug)
			{
				cout << "Received empty request" << endl;
			}
			break;
		}

		stringstream iss(request);
		//string request = get_request(client);
		
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
			if (cache == "")
			{
				success = send_response(client, "\n");
			}

			if (!success)
			{
				break;
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
			
			int len = stoi(message.params.at(2));
			while (len > req.length())
			{
				send_response(client, "\n");
				req += get_request (client);
			}

			message.value = req.substr (0, len);
						
			cache = req.substr (len, req.length()-1);
		}	//get_value(client, message, request);

		if (isDebug)
		{
			cout << "The request has been processed " << endl;
		}

		bool success = handle_message(client, message, (cache == "")); //send_response(client,request);
			
		if (isDebug)
		{
			cout << "The request has been handled " << endl;
		}
		// break if an error occurred
		if (!success)
		{
			break;
		}
	}
	close(client);
}

bool
Server::handle_message(int client, Message message, bool isSend) { 

	if (isDebug)
	{
		cout << "The request is being handled " << endl;
	}
	string msg;

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
	else if (message.command == "list")
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
				msg += to_string(i) + " " + it->second[i].first;
				if (i != it->second.size() - 1)
					msg+="\n";
			}
		}
	}
	else if (message.command == "get")
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
			msg += it->second[i].first + " " + to_string(it->second[i].second.length()) + "\n" + it->second[i].second;
		}
	}
	else if (message.command == "reset")
	{
		messages.clear()
		msg = "OK\n";
	}
	else 
	{
		msg = "error : incorrect command\n";
	}
	if (isSend == false)
	{
		return true;
	}

	if (isDebug)
	{
		cout << "Sending\n*******\n" << msg << "\n*******" endl;
	}
	return send_response(client, msg);
}

void
Server::get_value(int client, Message &message, string request) {
	bool success = send_response(client, "\n");
	if (not success)
		return;
	request = "";

	// read until we get a newline
	while (request.length() < stoi(message.params.at(1))) { // TODO: find out if this is neccisary
		int nread = recv(client,buf_,stoi(message.params.at(1)),0);
		if (nread < 0) {
			if (errno == EINTR)
				// the socket call was interrupted -- try again
				continue;
			else
				// an error occurred, so break out
				message.value = "";
		} else if (nread == 0) {
			// the socket is closed
			message.value = "";
		}
		// be sure to use append in case we have binary data
		request.append(buf_,nread);
	}
	// a better server would cut off anything after the newline and
	// save it in a cache
	message.value = request;
}

string
Server::get_request(int client) {
	string request = "";
	// read until we get a newline
	// int nread;
	// while ((nread = recv(client,buf_,1024,0)) > 0) {
	while (request.find("\n") == string::npos) {
        int nread = recv(client,buf_,1024,0);
		if (nread < 0) {
			if (errno == EINTR)
				// the socket call was interrupted -- try again
			{
				continue;
			}
			else
			{
				// an error occurred, so break out
				return "";
			}
		} else if (nread == 0) {
			// the socket is closed
			return "";
		}
		// be sure to use append in case we have binary data
		request.append(buf_,nread);
	}
	// a better server would cut off anything after the newline and
	// save it in a cache
	return request;
}

bool
Server::send_response(int client, string response) {

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
	return true;
}
