#include "Dog.h"


Dog::Dog(string name) : Animal(name)
{
}

string Dog::speak()
{
	return "WOOF";
}

Dog::~Dog(void)
{
}
