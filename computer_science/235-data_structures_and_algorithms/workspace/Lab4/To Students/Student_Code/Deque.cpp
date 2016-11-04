/*
 * Deque.cpp
 *
 *  Created on: May 25, 2014
 *      Author: misterpink14
 */

#include "Deque.h"
#include "iostream"


bool Deque::addToDequeLeft(Car* &Current)
{
	if (Current == NULL || size == 5)
	{
		return false;
	}
	else if (DequeHead == NULL)
	{
		++size;
		DequeHead = Current;
		DequeTail = Current;
		Current = NULL;
		return true;
	}
	else
	{
		++size;
		Current->next = DequeTail;
		DequeTail->prev = Current;
		DequeTail = DequeTail->prev;
		Current = NULL;
		return true;
	}
}


bool Deque::addToDequeRight(Car* &Current)
{
	if (Current == NULL || size == 5)
		{
			return false;
		}
		else if (DequeHead == NULL)
		{
			++size;
			DequeHead = Current;
			DequeTail = Current;
			Current = NULL;
			return true;
		}
		else
		{
			++size;
			Current->prev = DequeHead;
			DequeHead->next = Current;
			DequeHead = DequeHead->next;
			Current = NULL;
			return true;
		}
}


bool Deque::removeFromDequeLeft(Car* &Current)
{
	if(DequeHead == NULL)
	{
		return false;
	}
	else if(Current == NULL)
	{
		if(DequeHead == DequeTail)
		{
			Current = DequeHead;
			DequeTail = NULL;
			DequeHead = NULL;
		}
		else// if (Current == NULL)
		{
			Current = DequeTail;
			DequeTail = DequeTail->next;
			DequeTail->prev = NULL;
		}
		--size;
		return true;
	}
	else
	{
		return false;
	}
}


bool Deque::removeFromDequeRight(Car* &Current)
{
	if(DequeHead == NULL)
	{
		return false;
	}
	else if (Current == NULL)
	{
		if(DequeHead == DequeTail)
		{
			Current = DequeHead;
			DequeTail = NULL;
			DequeHead = NULL;
		}
		else// if (Current == NULL)
		{
			Current = DequeHead;
			DequeHead = DequeHead->prev;
			DequeHead->next = NULL;;
		}
		--size;
		return true;
	}
	else
	{
		return false;
	}
}


int Deque::showTopOfDequeLeft()
{
	if(DequeHead == NULL)
	{
		return -1;
	}
	else
	{
		return DequeTail->id;
	}
}


int Deque::showTopOfDequeRight()
{
	if(DequeHead == NULL)
	{
		return -1;
	}
	else
	{
		return DequeHead->id;
	}
}


int Deque::showSizeOfDeque()
{
	return size;
}


bool Deque::find(int car)
{
	Car* n = DequeHead;
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
