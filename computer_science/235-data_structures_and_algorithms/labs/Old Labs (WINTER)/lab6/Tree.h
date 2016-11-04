#include <string>
#include <iostream>
#include <iomanip>
#include <fstream>

using std::endl;

#pragma once

template <typename ItemType>

class Tree
{
private:
	struct Node{
		ItemType item;
		int height;
		Node* right;
		Node* left;

		Node(): left(NULL), right(NULL) {}

		Node(ItemType& it)
		{
			item = it;
			left = NULL;
			right = NULL;
			height = 0;
		}

//		Node(ItemType& it, Node* l, Node* r)
//		{
//			item = it;
//			left = l;
//			right = r;
//			height = 0;
//		}

		

		~Node()
		{
			delete left;
			delete right;
		}
	};

	int count;
	Node* root;


public:
	Tree(): root(NULL), count(0) {}


	int findDepth(Node* n)
	{
		if(n->right != NULL && n->left != NULL)
		{
			int a = findDepth(n->right);
			a++;
			int b = findDepth(n->left);
			b++;
			if (a < b)
				return a;
			else
				return b;
		}
		if(n->right != NULL )
		{
			int a = findDepth(n->right);
			a++;
			return a;
		}
		else if(n->left != NULL)
		{
			int a = findDepth(n->left);
			a++;
			return a;
		}
		else if(n->left == NULL && n->right == NULL)
			return 1;
	}


	void Check(Node* n)
	{
		int balance = findDepth(n->left) - findDepth(n->right);
		//IF tree is right heavy
		if(balance > 1)
		{
			n = n->right;
			balance = findDepth(n->left) - findDepth(n->right);
			//IF tree's right subtree is left heavy
			if(balance > 1)
			{
				//Perform Double Left rotation 
			}
			else
			{
				//Perform Single Left rotation
			}
		}
		//ELSE IF tree is left heavy
		else if(balance < -1)
		{
			n = n->left;
			balance = findDepth(n->left) - findDepth(n->right);
			//IF tree's left subtree is right heavy
			if(balance > 1)
			{
				//Perform Double Right rotation
			}
			else
			{
				//Perform Single Right rotation
			}
		}
	}



	void Add(ItemType& item) 
	{

		root = Add(root, item);

	}

	Node* Add(Node*& n, ItemType& it) 
	{
		if(n == NULL)
			return new Node(it);
		else if(it < n->item)
		{
			n->left = Add(n->left, it);
			//rebalance();
		}
		else if(it > n->item)
		{
			n->right = Add(n->right, it);
		}
		
		return n;
	}



	void Remove(const ItemType& item)
	{
		root = Remove(root, item);
	}

	Node* Remove(Node* n, const ItemType& item) 
	{
		if(n == NULL)
			return NULL;
		else if(item < n->item)
			n->left = Remove(n->left, item);
		else if(item > n->item)
			n->right = Remove(n->right, item);
		else if(n-> left == NULL && n->right == NULL)
			return NULL;
		else if(n->left == NULL)
			return n->right;
		else if(n->right == NULL)
			return n->left;
		else
		{
			n->item = findMin(n->right);
			n-> right = Remove(n->right, n->item);
		}

		//Check(n);
		return n;
	}



	ItemType findMin(Node* n)    // tree can't be empty
	{
		if(n->left == NULL)
			return n->item;
		else
			findMin(n->left);
	}
	
	ItemType Find (ItemType it)
	{
		Find(root,it);
	}
	
	ItemType Find (Node* n, ItemType it)
	{
		if (n == NULL)
			return "false";
		else if (it > n->item)
			return Find(n->right, it);
		else if (it < n->item)
			return Find(n->left, it);
		else
			return "true";
	}

	void Print(std::ofstream &out)
	{
		Print(out, root, 0);
	}

	void Print(std::ofstream &out, Node* n, int level)
	{
		if (root == NULL)
			return;
		int i;
		if (n!=NULL)
		{
			Print(out, n->right, level + 1);
			out << std::endl;
//			if (n == root)
				out<<"level " << level << ": ";
			/*for (i = 0; i < level && n != root; i++)
				out<<"        ";*/
			out<<n->item;
			Print( out, n->left, level + 1);
		}
//		out << "\nlevel " << root->item;
//		out << "\nlevel " << root->right->item;
	}


	~Tree() 
	{
		delete root;
	}
};
