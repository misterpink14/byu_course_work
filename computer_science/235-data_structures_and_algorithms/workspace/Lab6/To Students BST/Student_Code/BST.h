/*
 * BST.h
 *
 *  Created on: Jun 1, 2014
 *      Author: misterpink14
 */

#ifndef BST_H_
#define BST_H_

#include "Node.h"
#include "BSTInterface.h"


class BST : public BSTInterface
{

		// PRIVATE MEMBERS
	private:
		Node* Root;

		/**
		 * Recursive add function.
		 *
		 */
		bool add(int & data, Node* Current)
		{

			if (Current->getData() == data)
			{
				return false;
			}
			if (Current->getData() > data)
			{	// go left
				if(Current->getLeftChild() == NULL)
				{
					Node* n = new Node(data, NULL, NULL);
					Current->left = n;
					return true;
				}
				else
				{
					if(add(data, Current->getLeftChild()))
						return true;
					else
						return false;
				}
			}
			else
			{
				if(Current->getRightChild() == NULL)
				{
					Node* n = new Node(data, NULL, NULL);
					Current->right = n;
					return true;
				}
				else
				{
					if(add(data, Current->getRightChild()))
						return true;
					else
						return false;
				}
			}
		}





		bool find(int data, Node*& Remove, Node*& Previous)
		{

			if( Remove->getData() == data )
			{

				return true;
			}
			if( Remove->left == NULL && Remove->right == NULL )
			{
				return false;
			}
			if( data > Remove->getData() )
			{
				if ( Remove->right == NULL )
				{
					return false;
				}
				Previous = Remove;
				Remove = Remove->right;
				if ( find(data, Remove, Previous) )
				{
					return true;
				}
				return false;
			}
			else if( data < Remove->getData() )
			{
				 if ( Remove->left == NULL )
				 {
					 return false;
				 }
				 Previous = Remove;
				 Remove = Remove->left;
				 if ( find(data, Remove, Previous) )
				 {
					 return true;
				 }
				 return false;
			}
			return false;
		}



		void replace(Node*& Replace, Node*& Previous)
		{
			if ( Replace->getRightChild() != NULL )
			{
				 Previous = Replace;
				 Replace = Replace->right;
				 replace(Replace, Previous);
			}
			return;
		}


		/**
		 * Recursive remove function.
		 *
		 */
		bool Remove(int data)
		{

			Node* Remove = Root;
			Node* Previous = NULL;
			// find Remove and Previous
			if(!find(data, Remove, Previous))
			{
				return false;
			}


			bool prev = true;

			if ( Previous == NULL || Previous->data == Remove->data)
			{
				prev = false;
			}

			if( Remove->getLeftChild() == NULL && Remove->getRightChild() == NULL)
			{	// Leaf node case

				if ( prev && Previous->getLeftChild() != NULL && Previous->getLeftChild()->data == data)
				{
					Previous->left = NULL;
					delete Remove;
					return true;
				}
				else
				{	// Previous Left child is NULL

					if (prev)
					{	// there is a previous value
						Previous->right = NULL;
					}
					else
					{
						Root = NULL;
					}
					delete Remove;
					return true;
				}
			}
			if ( Remove->left == NULL )
			{	// Can't go left
				if (prev)
				{	// there is a previous value

					if(Previous->getRightChild() != NULL && Previous->right->data == data)
					{	// if data = Previous right
						Previous->right = Remove->getRightChild();
					}
					else
					{
						Previous->left = Remove->getRightChild();
					}
				}
				else
				{
					Root = Remove->getRightChild();
				}
				Remove->right = NULL;
				delete Remove;
				return true;
			}

			// Find a replacement
			bool rprev;
			Node* RPrevious = NULL;
			Node* Replace = NULL;

			// Get Replace
			Replace = Remove->getLeftChild();
			replace(Replace, RPrevious);

			if(RPrevious == NULL || RPrevious->data == Replace->data)
			{
				rprev = false;
			}
			else
			{
				rprev = true;
			}

			if (rprev)
			{	// if you went left then all the way right

				if(Replace->getLeftChild() != NULL)
				{
					RPrevious->right = Replace->left;
				}
				else
				{
					RPrevious->right = NULL;
				}
				Remove->data = Replace->data;
				delete Replace;
				return true;
			}
			else
			{	// you went left once
				if(Replace->getLeftChild() == NULL)
				{	// if there is no left child
					Remove->left = NULL;
					Remove->data = Replace->data;
					delete Replace;
				}
				else
				{
					Remove->data = Replace->data;
					Remove->left = Replace->left;
					delete Replace;
				}
				return true;
			}





////			if ( Remove->getRightChild() == NULL )
//			{
//				if (prev)
//				{
//					RPrevious->left = Replace->getLeftChild();
//				}
//				if (Replace != NULL)
//				{
//					if(Replace->getLeftChild() != NULL)
//					Remove->data = Replace->data;
//					delete Replace;
//				}
//				else
//				{
//					delete Remove;
//				}
//				return true;
//			}
//			return false;

		}



		/**
		 * Recursive clear function
		 *
		 */
		void Clear()
		{
			if(Root == NULL)
			{
				return;
			}
			while(Root != NULL)
			{
				Remove(Root->data);
			}

//			if(n == NULL)
//			{
//				return;
//			}
//			if(n->getLeftChild() == NULL && n->getRightChild() == NULL)
//			{
//				delete n;
//				return;
//			}
//			if(n->getLeftChild() == NULL)
//			{
//				clear(n->getRightChild());
//			}
//			else// if(n->getRightChild() == NULL)
//			{
//				clear(n->getLeftChild());
//				delete n;
//			}
//
//			if(n->getLeftChild() == NULL && n->getRightChild() == NULL)
//			{
//				delete n;
//				return;
//			}
//			else
//			{
//				clear(n);
//			}
		}



		// PUBLIC MEMBERS
	public:
		BST() : Root(NULL) {}
		~BST() { clear(); }

	//Please note that the class that implements this interface must be made
	//of objects which implement the NodeInterface

	/*
	 * Returns the root node for this tree
	 *
	 * @return the root node for this tree.
	 */
	Node * getRootNode()
	{
		if (Root == NULL)
		{
			return NULL;
		}
		return Root;
	}

	/*
	 * Attempts to add the given int to the BST tree
	 *
	 * @return true if added
	 * @return false if unsuccessful (i.e. the int is already in tree)
	 */
	bool add(int data)
	{

		if(Root == NULL)
		{
			Root = new Node(data, NULL, NULL);
			return true;
		}
		else
		{
			return add(data, Root);
		}
	}

	/*
	 * Attempts to remove the given int from the BST tree
	 *
	 * @return true if successfully removed
	 * @return false if remove is unsuccessful(i.e. the int is not in the tree)
	 */
	bool remove(int data)
	{

		if(Root == NULL)
		{
			return false;
		}
		else
		{
			return Remove(data);
		}
	}

	/*
	 * Removes all nodes from the tree, resulting in an empty tree.
	 */
	void clear()
	{

		if (Root == NULL)
		{
			return;
		}
		else
		{
			Clear();
			Root = NULL;
		}
	}
};




#endif /* BST_H_ */
