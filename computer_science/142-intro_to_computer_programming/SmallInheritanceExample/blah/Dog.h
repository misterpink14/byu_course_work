#pragma once
#include "Animal.h"

class Dog: public Animal
{
public:
	Dog(string name);
	virtual string speak();
	~Dog(void);
};

