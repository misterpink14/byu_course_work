#include "Animal.h"


Animal::Animal(string name)
{
	this->name = name;
}

string Animal::getName()
{
	return this->name;
}

Animal::~Animal(void)
{
}
