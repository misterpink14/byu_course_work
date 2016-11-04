/*
 * Node.h
 *
 *  Created on: Jun 5, 2014
 *      Author: misterpink14
 */

#ifndef NODE_H_
#define NODE_H_

#include "stddef.h"
#include "Person.h"

struct Node
{
	Person item;
	Node* next;
	Node* prev;

	Node()
	{
		//item = NULL;
		next = NULL;
		prev = NULL;
	};
	~Node() { next = NULL; }
	Node(Person value, Node* n = NULL, Node* h = NULL)
	{
		item = value;
		next = n;
		prev = h;
	};
};



#endif /* NODE_H_ */
