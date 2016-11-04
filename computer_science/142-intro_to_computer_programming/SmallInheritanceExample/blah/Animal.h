#pragma once
#include <string>

using namespace std;

class Animal
{
public:
	Animal(string name);
	~Animal(void);

	virtual string speak() = 0;
	virtual string getName();

protected:
	string name;

};

