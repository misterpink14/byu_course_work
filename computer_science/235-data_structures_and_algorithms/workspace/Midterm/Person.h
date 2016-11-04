/*
 * Person.h
 *
 *  Created on: Jun 4, 2014
 *      Author: misterpink14
 */

#ifndef PERSON_H_
#define PERSON_H_

#include <string>
#include <iostream>

class Person
{
public:
	std::string name;
	int speed;
	int str;


	Person();

	Person(std::string n, int sp, int st);

	~Person(){}

	void Display();


};



#endif /* PERSON_H_ */
