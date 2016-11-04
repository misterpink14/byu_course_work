#pragma once

#include <string>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sstream>
#include <fstream>
#include <iostream>

using namespace std;

class Message {
public:
	string command;
	vector<string> params;
	string value;
	bool isNeeded;

	Message (stringstream &iss);
};
