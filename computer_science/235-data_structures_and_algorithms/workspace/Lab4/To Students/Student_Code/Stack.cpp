/*
 * Stack.cpp
 *
 *  Created on: May 25, 2014
 *      Author: misterpink14
 */

#include "Stack.h"


bool Stack::addToStack(Car* &Current)
{
	if(Current == NULL || size == 5)
	{
		return false;
	}
	else if(StackHead == NULL)
	{
		++size;
		StackHead = Current;
		Current = NULL;
		return true;
	}
	else
	{
		++size;
		Current->prev = StackHead;
		StackHead->next = Current;
		StackHead = StackHead->next;
		Current = NULL;
		return true;
	}
}


bool Stack::removeFromStack(Car* &Current)
{
	if(StackHead == NULL)
	{
		return false;
	}
	else if(Current == NULL)
	{
		Current = StackHead;
		StackHead = StackHead->prev;
		StackHead->next = NULL;
		--size;
		return true;
	}
	else
	{
		return false;
	}
}


int Stack::showTopOfStack()
{
	if(StackHead == NULL)
	{
		return -1;
	}
	else
	{
		return StackHead->id;
	}
}


int Stack::showSizeOfStack()
{
	return size;
}


bool Stack::find(int car)
{
	Car* n = StackHead;
	while (n != NULL)
	{
		if (n->id == car)
		{
			return true;
		}
		n = n->prev;
	}
	return false;
}

