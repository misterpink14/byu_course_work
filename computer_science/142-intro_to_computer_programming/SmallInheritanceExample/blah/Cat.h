#pragma once
#include "Animal.h"

class Cat: public Animal
{
public:
	Cat(string name);

	virtual string speak();
	~Cat(void);
};

