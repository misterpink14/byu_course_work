#include <string>
#include <iostream>
#include <algorithm>
#include <cmath>
#include <iomanip>
#include <fstream>


#pragma once
template <typename ItemType>

class LinkedList
{

private:

	// Node
	struct Node {
		ItemType item;
		Node* next;
		Node() : next(NULL)
		{
//			item = NULL;
//			next = NULL;
		}
		Node(ItemType i, Node* n) 
		{
			item = i;//item = NULL;
			next = n;//next = NULL;
		}
		~Node()
		{
			next = NULL;
		}
	};

	int count;		// size of list
	Node* front;	// front of list
	//Node* back;		// back of list
	
	
		
 public:

	// Linkedlist
//	LinkedList() : 
		//Node(NULL),
	//	count(0),
	//	front(NULL)
		//tail(NULL)
//	{}
	LinkedList ()
	{
		count = 0;
		front = NULL;
	}; //: //Node(),count(0), front(NULL){}


	// size of List
	int size(){ return count; }


	// should work
	// clear all
	void Clear()
	{
		Node* n = front;
		while(n!=NULL)
		{
			front = front->next;
			delete n;
			n = front;
		}
		count = 0;
	//	front = NULL;
	}



	// should work
	// insert item at index
	void Insert(int &index, ItemType &name)
	{
		if (count < index)		//definately works
		{
			return;
		}
		else if (front == NULL)		// workss
		{
			count++;
			Node* n = new Node(name, NULL);
			this->front = n;
			return;
		}
		else
		{
			Node *n = this->front;
			Node *h = this->front;

			for (int place = 0;place < count+1; place++)
			{
				if (place == index)
				{
					count++;
					if (index == count-1)
					{
						Node* a = new Node(name, NULL);
						h->next=a;
					}
					else
					{
						Node *a = new Node();
						
						a->item = n->item;
						n->item = name;
						a->next = n->next;

						n->next = a;
					}
					break;
				}

				if (place!=0)
					h=n;
				n = n->next;
			}
		}
	}


	// remove item at index
	ItemType Remove(int &index)
	{
		if (index > count - 1)
			return "";
		Node *n = front;
		ItemType name;
		for (int i = 0; i < index-1; i++)
			n = n->next;
		if (index == 0)
		{
			front = n->next;
			name = n->item;
			delete n;
		}
		else
		{
			Node* h = n->next;
			n->next = h->next;
			name = h->item;
			delete h;
		}
		
		count--;
		
		if(count == 0)
		{
			front = NULL;
		}
		return name;
	}

	//************************WORKKSS
	int Find(ItemType &name)
	{
		Node *n = front;
		for (int i = 0; i < count; i++)
		{
			if (n->item == name)
				return i;
			else
				n = n->next;
		}
		return -1;
	}


	//***********************WORKSSS
	void Print(std::ofstream &out)
	{
		Node *n = front;
		if (n == NULL)
			return;
		for (int i = 0; i < count; i++)
		{
			out << std::endl << "node " << i << ": " << n->item;
			n=n->next;
		}
	}


	// deconstructor
	~LinkedList()
	{
		count = 0;
		while(front!=NULL)
		{
			Node* n = front;
			front = front->next;
			delete n;
		}
		//delete[] front;
		//delete[] prev;
		//count = 0;
	}
};
