#include "Cat.h"


Cat::Cat(string name) : Animal(name)
{
}

string Cat::speak()
{
	return "MEOW";
}

Cat::~Cat(void)
{
}
