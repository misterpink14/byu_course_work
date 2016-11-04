/*
 * Queue.cpp
 *
 *  Created on: May 25, 2014
 *      Author: misterpink14
 */

#include "Queue.h"


bool Queue::addToQueue(Car* &Current)
{
	if (Current == NULL || size == 5)
	{
		return false;
	}
	else if (QueueHead == NULL)
	{
		++size;
		QueueHead = Current;
		QueueTail = Current;
		Current = NULL;
		return true;
	}
	else
	{
		++size;
		Current->next = QueueTail;
		QueueTail->prev = Current;
		QueueTail = QueueTail->prev;
		Current = NULL;
		return true;
	}
}


bool Queue::removeFromQueue(Car* &Current)
{
	if(QueueHead == NULL)
	{
		return false;
	}
	else if (Current == NULL)
	{
		if(QueueHead == QueueTail)
		{
			Current = QueueHead;
			QueueTail = NULL;
			QueueHead = NULL;
		}
		else
		{
			Current = QueueHead;
			QueueHead = QueueHead->prev;
			QueueHead->next = NULL;
		}
		--size;
		return true;
	}
	else
	{
		return false;
	}
}


int Queue::showTopOfQueue()
{
	if(QueueHead == NULL)
	{
		return -1;
	}
	else
	{
		return QueueHead->id;
	}
}


int Queue::showSizeOfQueue()
{
	return size;
}


bool Queue::find(int car)
{
	Car* n = QueueHead;
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
