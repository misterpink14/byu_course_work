/*
 * Car.h
 *
 *  Created on: May 25, 2014
 *      Author: misterpink14
 */

#ifndef CAR_H_
#define CAR_H_

#include "stddef.h"

using namespace std;

struct Car
{
		int id;
		Car* next;
		Car* prev;

		Car();
		~Car(){}

		Car(int car, Car* n, Car* p);
};



#endif /* CAR_H_ */
