#include "AVLInterface.h"
#include "Node.h"
#include <algorithm>
#include <fstream>
#include <queue>
#include <sstream>
#include <cstdlib>
#include <ctime>
#include <iostream>

using namespace std;

class AVL: public AVLInterface
{
	
private:

	Node* root;
	
public:

	AVL() 
	{
		root = NULL;
	}
	~AVL() {}
	
	Node* getRootNode()
	{
		return root;
	}
	
	int checkBalance(Node* n)
	{
		if (n->getRightChild() == NULL && n->getLeftChild() == NULL)
		{
			return 0;
		}
		
		else if (n->getRightChild() == NULL)
		{
			////cout << "11111111111111" << endl;
			return (-1)-(n->getLeftChild()->getHeight());
		}
		
		else if (n->getLeftChild() == NULL)
		{
			////cout << "222222222222222" << endl;
			////cout << n->getRightChild()->getData() << endl;
			return n->getRightChild()->getHeight()-(-1);
		}
		
		else
		{
			////cout << "333333333333333" << endl;
			return ( (n->getRightChild()->getHeight()) - (n->getLeftChild()->getHeight()) );
		}
	}
	
	int findHeight (Node* n)
	{
		int heightLeft;
		int heightRight;
		
		if (n->getLeftChild() == NULL)
		{
			heightLeft = -1;
		}
		else
		{
			heightLeft = n->getLeftChild()->getHeight();
		}
		
		if (n->getRightChild() == NULL)
		{
			heightRight = -1;
		}
		else
		{
			heightRight = n->getRightChild()->getHeight();
		}
		
		if (heightLeft > heightRight)
		{
			return (heightLeft + 1);
		}
		else
		{
			return (heightRight + 1);
		}
	}
	
	void rightRotate (Node* &n)
	{
		Node* temp = n->getLeftChild();
		n->setLeftChild(temp->getRightChild());
		temp->setRightChild(n);
		n = temp;
		n->getRightChild()->setHeight(findHeight(n->getRightChild()));
		n->setHeight(findHeight(n));
	}
	
	void leftRotate (Node* & n)
	{
		Node* temp = n->getRightChild();
		n->setRightChild(temp->getLeftChild());
		temp->setLeftChild(n);
		n = temp;
		n->getLeftChild()->setHeight(findHeight(n->getLeftChild()));
		n->setHeight(findHeight(n));
		//cout << n->getData() << endl;
		
	}
	
	void adjustParent (Node*& n, Node*& parent, string side)
	{
		//cout << "iiiiiiiiiii " << n->getData() << " " << parent->getData() << endl;
		if (parent->getData() == n->getData())
		{
			//cout << "heeeeeeeeeeyyyyyyyyy" << endl;
			return;
		}
		
		if (side == "left")
		{
			//cout << side << endl;
			parent->setLeftChild(n);
		}
		else
		{
			//cout << side << endl;
			parent->setRightChild(n);
		}
	}
		
	
	void balance (Node*& n, Node*& parent, string side)
	{
		int balance = checkBalance(n);
		
		
		//cout << n->getData() << " " << balance << " " << n->getHeight() << endl;
		
		if (n->getData() > parent->getData())
		{
			side = "right";
		}
		else
		{
			side = "left";
		}
		
		if (balance == -2)
		{
			//cout << "-2" << endl;
			
			if (checkBalance(n->getLeftChild()) == -1)
			{
				//cout << "-1" << endl;
				rightRotate(n);
				
				if (parent != n->getRightChild())
				{
					adjustParent(n, parent, side);
				}
				//adjustParent(n, parent, side);
			}
			
			else if (checkBalance(n->getLeftChild()) == 1)
			{
				//cout << "1" << endl;
				Node* temporary = n->getLeftChild();
				leftRotate(temporary);
				if (parent != n->getLeftChild())
				{
					adjustParent(n, parent, side);
				}
				rightRotate(temporary);
				if (parent != n->getRightChild())
				{
					adjustParent(n, parent, side);
				}
				//adjustParent(n, parent, side);
			}
			
			else if (checkBalance(n->getLeftChild()) == 0)
			{
				//cout << "0" << endl;
				rightRotate(n);
				if (parent != n->getRightChild())
				{
					adjustParent(n, parent, side);
				}
				//adjustParent(n, parent, side);
			}
		}
		
		else if (balance == 2 )
		{
			//cout << "2" << endl;
			
			if (checkBalance(n->getRightChild()) == 1)
			{
				//cout << "1" << endl;
				leftRotate(n);
				//cout << "n " << n->getData() << " parent " << parent->getData() << endl;
				if (parent != n->getLeftChild())
				{
					adjustParent(n, parent, side);
				}
			}
			
			else if (checkBalance(n->getRightChild()) == -1)
			{
				//cout << "-1" << endl;
				Node* temporary = n->getRightChild();
				//cout << "n " << n->getData() << " parent " << parent->getData() << " right child " << parent->getRightChild()->getData() << endl;
				rightRotate(temporary);
				//cout << "n " << n->getData() << " parent " << parent->getData() << " right child " << parent->getRightChild()->getData() << endl;
				if (parent != n->getRightChild())
				{
					adjustParent(n, parent, side);
				}
				//cout << "n " << n->getData() << " parent " << parent->getData() << " right child " << parent->getRightChild()->getData() << endl;

				leftRotate(temporary);
				
				if (n->getData() >= parent->getData())
				{
					side = "right";
				}
				else
				{
					side = "left";
				}
				//cout << "n " << n->getData() << " parent " << parent->getData() << " left child " << n->getLeftChild()->getData() << endl;
				if (parent != n->getLeftChild())
				{
					adjustParent(n, parent, side);
				}
				//cout << "n " << n->getData() << " parent " << parent->getData() << " right child " << parent->getRightChild()->getData() << endl;
				//adjustParent(n, parent, side);
			}
			
			else if (checkBalance(n->getRightChild()) == 0)
			{
				//cout << "0" << endl;
				leftRotate(n);
				if (parent != n->getLeftChild())
				{
					adjustParent(n, parent, side);
				}
				//adjustParent(n, parent, side);
			}
		
		
		}
	}
		
	
	void adder(int data, Node* n, bool &added, Node* parent) 
	{
		if (n == NULL)
		{
			n = new Node;
			n->setData(data);
			n->setLeftChild(NULL);
			n->setRightChild(NULL);
			n->setHeight(0);
			
			
			if (parent != NULL)
			{
				if (n->getData() < parent->getData())
				{
					parent->setLeftChild(n);
				}
				else if (n->getData() > parent->getData())
				{
					parent->setRightChild(n);
				}
			}
	
			root = n;
			added = true;
			return;
		}

		else if (n->getData() == data)
		{
			added = false;
			return;
		}

		else if (data < n->getData())
		{
			Node* leftie = n->getLeftChild();
			adder(data, leftie, added, n);
			balance(n, parent, "left");
			n->setHeight(findHeight(n));
			root = n;
			return;
		}

		else
		{
			////cout << "call this"  << n->getData() << endl;
			Node* rightie = n->getRightChild();
			adder(data, rightie, added, n);
			////cout << "balance" << n->getData() << " " << parent->getData() << endl;
			balance(n, parent, "right");
			////cout << "after " << n->getData() << endl;
			////cout << root->getData() << endl;
			n->setHeight(findHeight(n));
			root = n;
			////cout << root->getData() << endl;
			return;
		}

	}
	
	
	bool add(int data)
	{
		////cout << "add " << data << endl;
		
		bool added = false;
		
		adder(data, root, added, root);
		
		if (added == true)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	
	Node* getLargest(Node* n)
	{
		
		if (n->getRightChild() != NULL)
		{
			getLargest(n->getRightChild());
		}
		else
		{
			return n;
		}
	}
	
	Node* getSmallestParent(Node* smallestParent, Node* smallest, Node* &smallestParentParent)
	{
		if (smallestParent->getRightChild() == smallest)
		{
			return smallestParent;
		}
		else if (smallestParent->getRightChild() != NULL)
		{
			smallestParentParent = smallestParent;
			return getSmallestParent(smallestParent->getRightChild(), smallest, smallestParentParent);
		}
		else
		{
			////cout << "Error";
			return getSmallestParent(smallestParent->getRightChild(), smallest, smallestParentParent);
		}
	}
	
	void remover(Node* n, int data, bool &removed, Node* parent)
	{
		if (n == NULL)
		{
			return;
		}
		
		if (n->getData() == data)
		{
			if (n->getLeftChild() == NULL && n->getRightChild() == NULL)
			{
				if (parent != NULL)
				{
					if (parent->getRightChild() == n)
					{
						parent->setRightChild(NULL);
					}
					else if (parent->getLeftChild() == n)
					{
						parent->setLeftChild(NULL);
					}
				}
				delete n;
				
				root = NULL;
				removed = true;
				return;
			}
			else if (n->getLeftChild() == NULL && n->getRightChild() != NULL)
			{
				if (parent->getLeftChild() == n)
				{
					parent->setLeftChild(n->getRightChild());
					root = parent->getLeftChild();
					delete n;
					removed = true;
					return;
				}
				else
				{
					if (parent == n)
					{
						
						root = n->getRightChild();
						delete n;
						return;
					}
					
					
					
					parent->setRightChild(n->getRightChild());
					root = parent->getRightChild();
					delete n;
					removed = true;
					return;
				}
			}
			else if (n->getRightChild() == NULL && n->getLeftChild() != NULL)
			{
				if (parent->getLeftChild() == n)
				{

					parent->setLeftChild(n->getLeftChild());
					delete n;
					root = parent->getLeftChild();
					removed = true;
					return;
				}
				else
				{
					if (parent == n)
					{
						
						Node* smallest = getLargest(n->getLeftChild());
						
						Node* smallestParent = n;
						Node* smallestParentParent = n;
						
						if (smallestParent->getLeftChild() != smallest)
						{
							smallestParent = getSmallestParent(smallestParent->getLeftChild(), smallest, smallestParentParent);
						}
						
						
						n->setData(smallest->getData());
					
						if (smallest->getLeftChild() == NULL)
						{
							if (smallestParent->getRightChild() == smallest)
							{
								smallestParent->setRightChild(NULL);
							}
							else
							{
								smallestParent->setLeftChild(NULL);
							}
						}
						else
						{
							////cout << "yoooooooooooooooooooooo" << smallest->getLeftChild()->getData() << endl;
							if (smallestParent->getRightChild() == smallest)
							{
								smallestParent->setRightChild(smallest->getLeftChild());
							}
							else
							{
								smallestParent->setLeftChild(smallest->getLeftChild());
							}
						}
						
						delete smallest;
						
						//balance(smallestParent, smallestParentParent, "right");
						//n->setHeight(findHeight(n));
						removed = true;
						root = n;
						return;
						
					
					}
					
						
					Node* smallest = getLargest(n->getLeftChild());
				
					////cout << "smallest" << smallest->getData() << endl;
					
					//////////////////////////////
					
					Node* smallestParent = n;
					Node* smallestParentParent = n;
					
					if (smallestParent->getLeftChild() != smallest)
					{
						smallestParent = getSmallestParent(smallestParent->getLeftChild(), smallest, smallestParentParent);
					}
					
					////cout << "smallest parent " << smallestParent->getData() << endl;
					////cout << "smallest " << smallest->getData() << endl;
					
					n->setData(smallest->getData());
				
					if (smallest->getLeftChild() == NULL)
					{
						if (smallestParent->getRightChild() == smallest)
						{
							smallestParent->setRightChild(NULL);
						}
						else
						{
							smallestParent->setLeftChild(NULL);
						}
					}
					else
					{
						////cout << "yoooooooooooooooooooooo" << smallest->getLeftChild()->getData() << endl;
						if (smallestParent->getRightChild() == smallest)
						{
							smallestParent->setRightChild(smallest->getLeftChild());
						}
						else
						{
							smallestParent->setLeftChild(smallest->getLeftChild());
						}
					}
					
					delete smallest;
					
					//balance(smallestParent, smallestParentParent, "right");
					//n->setHeight(findHeight(n));
					removed = true;
					root = n;
					return;
							
				}
			}
			else
			{
				////cout << "left " << n->getLeftChild()->getData() << endl;

				Node* smallest = getLargest(n->getLeftChild());

				
				Node* smallestParent = n;
				Node* smallestParentParent = n;
				
				if (smallestParent->getLeftChild() != smallest)
				{
					smallestParent = getSmallestParent(smallestParent->getLeftChild(), smallest, smallestParentParent);
				}
				
				////cout << "smallest " << smallest->getData() << endl;
				
				
				n->setData(smallest->getData());
				
				if (smallest->getLeftChild() == NULL)
				{
					if (smallestParent->getRightChild() == smallest)
					{
						smallestParent->setRightChild(NULL);
					}
					else
					{
						smallestParent->setLeftChild(NULL);
					}
				}
				else
				{
					////cout << "yoooooooooooooooooooooo" << smallest->getLeftChild()->getData() << endl;
					if (smallestParent->getRightChild() == smallest)
					{
						smallestParent->setRightChild(smallest->getLeftChild());
					}
					else
					{
						smallestParent->setLeftChild(smallest->getLeftChild());
					}
				}
				
				//Node* smallestParentParent = getSmallestParentParent(n, smallestParent);
				
				//cout << "smallestParent" << smallestParent->getData() << endl;
				
				delete smallest;
				
				string side;
				
				if (smallestParentParent->getRightChild() == smallestParent)
				{
					side = "right";
				}
				else
				{
					side = "left";
				}
				
				
				//cout << "call me" << endl;
				balanceAll(root, root, side, smallestParent);
				
		
				
				removed = true;
				root = n;
				return;
				
				
			}
				
		}
		
		else if (n->getData() < data)
		{
			remover(n->getRightChild(), data, removed, n);
			
			balance(n, parent, "right");
			n->setHeight(findHeight(n));
			root = n;
			return;
		}
		else
		{
			remover(n->getLeftChild(), data, removed, n);
			//cout << "n " << n->getData() << " parent " << parent->getData() << endl;
			balance(n, parent, "left");
			n->setHeight(findHeight(n));
			root = n;
			return;
		}
	}
	
	void balanceAll(Node* n, Node* parent, string side, Node* smallestParent)
	{
		
		if (n->getData() < smallestParent->getData())
		{
			balanceAll(n->getRightChild(), n, "right", smallestParent);
			balance(n, parent, "right");
			n->setHeight(findHeight(n));
		}
		else if (n->getData() > smallestParent->getData())
		{
			balanceAll(n->getLeftChild(), n, "left", smallestParent);
			balance(n, parent, "left");
			n->setHeight(findHeight(n));
		}
		else
		{
			balance(n, parent, "right");
			n->setHeight(findHeight(n));
			return;
		}
	}
	
	void balanceEverything(Node*n, Node* parent, string side)
	{
		if (n != NULL)
		{
			balance(n, parent, side);
			n->setHeight(findHeight(n));
			balanceEverything(n->getLeftChild(), n, side);
			balanceEverything(n->getRightChild(), n, side);
			
		}
		else
		{
			return;
		}
	}
			
	
	bool remove(int data)
	{
		//cout << "remove " << data << endl;
		bool removed = false;
		remover(root, data, removed, root);
		
		if (removed == true)
		{
			return true;
		}
		else 
		{
			return false;
		}
	}
	
	void clear()
	{
		while (root != NULL)
		{
			////cout << "root " << root << " " << root->getData() << endl;
			////cout << "root left child " << root->getLeftChild()->getData()  << endl;
			////cout << "root right child " << root->getRightChild()->getData() << endl;
			bool removed = false;
			remover(root, root->getData(), removed, root);
			////cout << "root after " << root << " " << root->getData() << endl;
		}
	}
};
