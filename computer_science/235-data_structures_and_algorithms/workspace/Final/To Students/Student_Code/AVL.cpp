/*
 * AVL.cpp
 *
 *  Created on: Jun 18, 2014
 *      Author: misterpink14
 */

#include "AVL.h"




void AVL::rebalance(Node* n)
{
	///// << "rebalance\n";
			if (n == NULL || (n->left == NULL && n->right == NULL))
			{
				///// << "null\n";
				return;
			}

			if ((n->left == NULL && n->right != NULL && height(n->right) > 0) || (n->right != NULL && n->left != NULL && (height(n->right) - height(n->left)) < 0))
			{
				///// << "right\n";
				if ((n->right->right != NULL && n->right->left != NULL && (height(n->right->right) - height(n->right->left)) > 0) || (n->right->right != NULL && n->right->left == NULL && height(n->right->right) > 0))
				{
					///// << "dubs\n";
					DoubleRight(n);
				}
				else if((n->right->left != NULL && n->right->right != NULL && (height(n->right->left) - height(n->right->right)) > 0) || (n->right->left != NULL && n->right->right == NULL && height(n->right->left) > 0))
				{
					///// << "s\n";
					SingleRight(n);
				}
			}
			else if((n->right == NULL && height(n->left) > 0) || (height(n->right) - height(n->left)) > 0)
			{
				///// << "left\n";
				if ((n->left->left == NULL && n->left->right != NULL && (height(n->left->right) > 0)) || (n->left->right != NULL && n->left->left != NULL && (height(n->left->right) - (height(n->left->left)) > 0)))
				{
					///// << "dubs\n";
					DoubleLeft(n);
				}
				else if((n->left->right != NULL && n->left->left != NULL && (height(n->left->right) - height(n->left->left)) > 0) || (n->left->right != NULL && n->left->left == NULL && height(n->left->right) > 0))
				{
					///// << "s\n";
					SingleLeft(n);
				}
			}
			///// << "else\n";

}




void AVL::SingleLeft(Node*& n)
{
     Node *h;
    if (n->left == NULL)
    {
    	h = NULL;
    }
    else
    {
    	 h = n->left;
    if(h->right == NULL)
    {
    	n->left = NULL;
    }
    else
    {
    	n->left = h->right;
    }
    h->right = n;
    }

     n = h;
}


void AVL::DoubleLeft(Node*& n)
{
     SingleRight(n->left);
     SingleLeft(n);
}


void AVL::SingleRight(Node*& n)
{
     Node *h;
     if (n->right == NULL)
	 {
		h = NULL;
	 }
	 else
	 {
		 h = n->right;
	 if(h->left == NULL)
	 {
		n->right = NULL;
	 }
	 else
	 {
		n->right = h->left;
	 }
	 h->left = n;
	 }

	  n = h;

//	 h = n->right;
//     n->right = h->left;
//     h->left = n;
//     n = h;
}


void AVL::DoubleRight(Node*& n)
{
     SingleLeft(n->right);
     SingleRight(n);
}


int AVL::Height(Node*n)
{
	///// << "in " << n->height << endl;
	int count = 0;
	if (n == NULL)
	{
		return -1;
	}


	if (n->left == NULL && n->right == NULL)
	{
		///// << "in in1\n";
		// no child, the height is 0
		n->height = 0;
		return n->height;
	}

	if (n->left != NULL)
	{
		///// << "in in2\n";
		n->left->height = Height(n->left);
		count = n->left->height;
	}

	if (n->right != NULL)
	{
		///// << "in in3\n";
		 n->right->height = Height(n->right);
		if(count < n->right->height)
		{
			///// << "out in3\n";
			count = n->right->height;
		}
	}

	// include leaf in the height
	n->height = (count+1);
	return n->height;
}

int AVL::height(Node* n)//, int & h)
{


	int left, right;

	 if(n==NULL)
		 return -1;
	 left = height(n->left);
	 right = height(n->right);
	 if(left > right)
	 {
		n->height = left;
		n = NULL;

		return left+1;
	 }
	 else
	 {
		n->height = right;
		n = NULL;
		return right+1;
	 }
}



Node * AVL::add(int & data, Node* n)
{;
	if(n == NULL)
	{
		 n = new Node(data);
		 return n;
	}
	else if(data < n->data)
	{
		Node*h =  add( data, n->left);
		if(h == NULL)
		{
			return NULL;
		}
		n->left = h;
		if( height(n->left) - height(n->right) > 1)
		{
			if(data < n->left->data)
			{
				SingleLeft(n);
			}
			else
			{
				DoubleLeft(n);
			}
		}
		return n;
	 }
	 else if(data > n->data)
	 {
		Node*h = add(data, n->right);
		if (h == NULL)
		{
			return NULL;
		}
		n->right = h;
		if( (n->left == NULL && height(n->right) > 2) || ((height(n->right) - height(n->left)) > 1))
		{
			if(data > n->right->data)
			{
				SingleRight(n);
			}
			else
			{
				DoubleRight(n);
			}
		}
		return n;
	}
	else
	{
		return NULL;
	}
}






bool AVL::find(int data, Node*& Remove, Node*& Previous)
{

	if( Remove->getData() == data )
	{

		return true;
	}
	if( Remove->left == NULL && Remove->right == NULL )
	{
		return false;
	}
	//check = Previous;
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



void AVL::replace(Node*& Replace, Node*& Previous)
{
	if ( Replace->getRightChild() != NULL )
	{
		 Previous = Replace;
		 Replace = Replace->right;
		 replace(Replace, Previous);
	}
	return;
}



void AVL::rreplace(Node*& Replace, Node*& Previous)
{
	if ( Replace->getLeftChild() != NULL )
	{
		 Previous = Replace;
		 Replace = Replace->left;
		 replace(Replace, Previous);
	}
	return;
}




bool AVL::Remove(int data)
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
		///// << "close\n";
		if ( prev && Previous->getLeftChild() != NULL && Previous->getLeftChild()->data == data)
		{
			///// << "here\n";
			Previous->left = NULL;
			if (Remove->data == Root->data)
			{
				Root = NULL;
			}
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
}



Node* AVL::Remove(Node* n, int data, bool &ret)
{
	if (n == NULL)
	{
		return NULL;
	}
	///// << "removeees " << data << endl;
	Node* Replace = NULL;
	Node* RPrevious = NULL;
	if (data == n->data)
	{
		///// << "data\n";
		if(n->left == NULL && n->right == NULL)
		{	// leaf node
			///// << "leaf\n";
			if(n->data == Root->data)
			{
				///// << "root\n";
				delete Root;
				ret = true;
				n=NULL;
				Root = NULL;
				///// << "end root\n";
				return NULL;
			}
			else
			{
				///// << "not root" << n->data << " " << data << "\n";
				delete n;
				ret = true;
				///// << "deleted\n";
				return NULL;
			}
			///// << "end root\n";
//			return NULL;
		}
		else if(n->left !=NULL)
		{
			///// << "go left\n";
			Replace = n->left;
			replace(Replace, RPrevious);
			if(RPrevious == NULL)
			{	// moved left once
				n->data = Replace->data;
				n->left = NULL;
				if(Replace->left != NULL)
				{
					n->left = Replace->left;
				}
			}
			else
			{	// left then right
				n->data = Replace->data;
				RPrevious->right = NULL;
				if(Replace->left != NULL)
				{
					RPrevious->right = Replace->left;
				}
			}
			///// << "left\n";
			delete Replace;
			ret = true;
			Replace = NULL;
		}
		else
		{	// go right once
			///// << "go right\n";
			Replace = n->right;
			rreplace(Replace, RPrevious);
			if(RPrevious == NULL)
			{	// moved right once
				/////<< "rightonce\n";
				n->data = Replace->data;
				n->left = NULL;
				n->right = NULL;
				if(Replace->left != NULL)
				{
					n->left = Replace->left;
				}
			}
			else
			{	// right then left
				/////<< "rightl \n";
				n->data = Replace->data;
				RPrevious->left = NULL;
				if(Replace->right != NULL)
				{
					RPrevious->left = Replace->right;
				}
			}
			///// << "right\n";
			delete Replace;
			///// << "deleteR\n";
			ret = true;
			Replace = NULL;
		}
		if (n==NULL)
		{
			return NULL;
		}
		//Root->height = Height(Root);
		rebalance(n);
		return n;
	}
	if(data < n->data)
	{
		///// <<"left\n";
		Node* u = Remove(n->left, data, ret);
		n->left = NULL;
		if( u != NULL)
		{
			///// << "not null\n";
			n->left = u;

		}
		if (n == NULL)
		return NULL;
		else
		{
			//Root->height = Height(Root);
			rebalance(n);
			return n;
		}
	}
	if(data > n->data)
	{
		///// <<"right\n";
		Node* i =  Remove(n->right, data, ret);
		n->right = NULL;
		if(i != NULL)
		{//balance
			///// << "null not\n";
			n->right = i;
		}
		if (n == NULL)
		return NULL;
		else
		{
			//Root->height = Height(Root);
			rebalance(n);
			return n;
		}
	}

	//Root->height = Height(Root);
	rebalance(n);
	return n;
}



void AVL::Clear()
{
	if (Root == NULL)
	{
		return;
	}
	else
	{
		while(Root != NULL)
		{
			Remove(Root->data);
		}


		Root = NULL;
	}
}



AVL::AVL()
{
	Root = NULL;
}


AVL::~AVL()
{
	Clear();
}




Node * AVL::getRootNode()
{
	return this->Root;
}



bool AVL::add(int data)
{
	if(Root == NULL)
	{
		Root = new Node(data, 0, NULL, NULL);
		return true;
	}
	else
	{
		Node*n = add(data, Root);
		if( n == NULL )
		{
			Height(Root);
			return false;
		}
		Root = n;
		if(Root != NULL)
			Height(Root);
		return true;
	}
}




bool AVL::remove(int data)
{
	if(Root == NULL)
	{
		return false;
	}
	else
	{

		bool ret = false;
		Node* y = Remove(Root, data, ret);
		if(y == NULL)
		{
			if (Root != NULL)
				Root->height = Height(Root);
			return ret;
		}
		Root = y;
		if (Root != NULL)
			Root->height = Height(Root);
		return ret;
	}
}