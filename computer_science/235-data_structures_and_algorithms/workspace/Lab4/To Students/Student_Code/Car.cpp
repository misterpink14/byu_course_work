/*
 * Car.cpp
 *
 *  Created on: May 25, 2014
 *      Author: misterpink14
 */

#include "Car.h"


Car::Car() : id(-1), next(NULL), prev(NULL) {}

Car::Car(int car, Car* n, Car* p) : id(car), next(n), prev(p) {}
