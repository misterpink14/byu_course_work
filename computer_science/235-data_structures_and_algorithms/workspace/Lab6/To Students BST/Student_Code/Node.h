/*
 * Node.h
 *
 *  Created on: Jun 1, 2014
 *      Author: misterpink14
 */

#ifndef NODE_H_
#define NODE_H_

#include "NodeInterface.h"

class Node: public NodeInterface {

public:
	int data;
	Node* left;
	Node* right;


	Node() : data(0), left(NULL), right(NULL) {}

	Node(int d) : data(d), left(NULL), right(NULL) {}

	Node(int d, Node* l, Node* r) : data(d), left(l), right(r) {}

	~Node()
	{
		data = 0;
		left = NULL;
		right = NULL;
	}

	/*
	 * Returns the data that is stored in this node
	 *
	 * @return the data that is stored in this node.
	 */
	int getData()
	{
		return this->data;
	}

	/*
	 * Returns the left child of this node or null if it doesn't have one.
	 *
	 * @return the left child of this node or null if it doesn't have one.
	 */
	Node * getLeftChild()
	{
		return this->left;
	}

	/*
	 * Returns the right child of this node or null if it doesn't have one.
	 *
	 * @return the right child of this node or null if it doesn't have one.
	 */
	Node * getRightChild()
	{
		return this->right;
	}

};




#endif /* NODE_H_ */
