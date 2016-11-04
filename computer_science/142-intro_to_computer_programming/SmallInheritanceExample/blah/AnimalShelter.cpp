#include "Animal.h"
#include "Cat.h"
#include "Dog.h"
#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main()
{
	vector<Animal*>myAnimals;

	int option = 1;
	while (option != 0 )
	{
		cout << "1. Get a Dog" << endl;
		cout << "2. Get a Cat" << endl;
		cout << "3. All animals SPEAK! "<< endl;
		cin >> option;

		if (option == 1)
		{
			cout << "What will be the name of your dog?" << endl;
			string dogName;
			cin >> dogName;
			Animal* animal = new Dog(dogName);
			myAnimals.push_back(animal);
		}
		if (option == 2)
		{
			cout << "What will be the name of your cat?" << endl;
			string catName;
			cin >> catName;
			Animal* animal = new Cat(catName);
			myAnimals.push_back(animal);
		}
		if (option == 3 )
		{
			for ( int i =0; i < myAnimals.size(); i++)
			{
				cout << myAnimals[i]->getName() << ": " << myAnimals[i]->speak() << endl;
			}
		}
	}

	return 0;

}