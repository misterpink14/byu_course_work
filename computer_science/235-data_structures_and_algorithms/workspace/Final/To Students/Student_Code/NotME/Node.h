#include "NodeInterface.h"
#include <algorithm>
#include <fstream>
#include <queue>
#include <sstream>
#include <cstdlib>
#include <ctime>

using namespace std;

class Node : public NodeInterface
{
	
private:

	int data;
	Node* left;
	Node* right;
	int height;
	
public:

	Node() 
	{
		data = 0;
		left = NULL;
		right = NULL;
		height = 0;
	}
	~Node() {}
	
	int getData()
	{
		return data;
	}
	
	int setData(int data_in)
	{
		data = data_in;
	}
	
	Node* getLeftChild()
	{
		return left;
	}
	
	Node* setLeftChild(Node* left_in)
	{
		left = left_in;
	}
	
	Node* getRightChild()
	{
		return right;
	}
	
	Node* setRightChild(Node* right_in)
	{
		right = right_in;
	}
	
	int getHeight()
	{
		return height;
	}
	
	int setHeight(int height_in)
	{
		height = height_in;
	}
	
	
};
