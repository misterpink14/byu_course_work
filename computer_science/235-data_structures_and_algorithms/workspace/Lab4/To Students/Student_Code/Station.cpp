/*
 * Station.cpp
 *
 *  Created on: May 24, 2014
 *      Author: misterpink14
 */


#include "Station.h"



bool Station::Station::addToStation(int car)
{
	if(Current == NULL && car >= 0 && !q.find(car) && !s.find(car) && !d.find(car))
	{
		//Check the dt's
		Current = new Car(car, NULL, NULL);
		return true;
	}
	else
	{
		return false;
	}
}


int Station::Station::showCurrentCar()
{
	if (Current == NULL)
	{
		return -1;
	}
	else
	{
		return Current->id;
	}
}


bool Station::Station::removeFromStation()
{
	if(Current == NULL)
	{
		return false;
	}
	else
	{
		delete Current;
		Current = NULL;
		return true;
	}
}


bool Station::addToStack()
{
	return s.addToStack(Current);
}


bool Station::removeFromStack()
{
	return s.removeFromStack(Current);
}


int Station::showTopOfStack()
{
	return s.showTopOfStack();
}


int Station::showSizeOfStack()
{
	return s.showSizeOfStack();
}


bool Station::addToQueue()
{
	return q.addToQueue(Current);
}


bool Station::removeFromQueue()
{
	return q.removeFromQueue(Current);
}


int Station::showTopOfQueue()
{
	return q.showTopOfQueue();
}


int Station::showSizeOfQueue()
{
	return q.showSizeOfQueue();
}


bool Station::addToDequeLeft()
{
	return d.addToDequeLeft(Current);
}


bool Station::addToDequeRight()
{
	return d.addToDequeRight(Current);
}


bool Station::removeFromDequeLeft()
{
	return d.removeFromDequeLeft(Current);
}


bool Station::removeFromDequeRight()
{
	return d.removeFromDequeRight(Current);
}


int Station::showTopOfDequeLeft()
{
	return d.showTopOfDequeLeft();
}


int Station::showTopOfDequeRight()
{
	return d.showTopOfDequeRight();
}


int Station::showSizeOfDeque()
{
	return d.showSizeOfDeque();
}


