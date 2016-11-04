/*
 * main.cpp
 *
 *  Created on: Aug 31, 2014
 *      Author: misterpink14
 */

#include "C:\Users\Ben\Google Drive\235-Spring\workspace\Final\To Students\Student_Code\Me\AVL.h"
#include <iostream>

using namespace std;

//15s
void fivehundredtozero()
{
	AVL tree;// = new AVL();
	for (int i = 500; i >= 0; i-=15)
	{
		cout << "in \n";
		if(!tree.add(i))
		{
			cout << "ERRORR ADDING: " << i << ".\n";
			break;
		}
	}
}

//5s
void zerotofivehunred()
{
	AVL tree;// = new AVL();
	for (unsigned i = 0; i <= 500; i+=5)
	{
		if(!tree.add(i))
		{
			cout << "ERRORR ADDING: " << i << ".\n";
			break;
		}
	}

}

// and zero to -50
void zerotofifty()
{
	AVL tree;

	for (int i = 0; i <= 50; i++)
	{
		if(!tree.add(i))
		{
			cout << "1: ERRORR ADDING: " << i << ".\n";
			break;
		}
	}
	for (unsigned i = 0; i <= 50; i++)
	{
		if(!tree.add(-1*i))
		{
			cout << "2: ERRORR ADDING: " << -1*i << ".\n";
//			break;
		}
	}
}

// print to file
void print(AVL &tree)
{
	Node* n = tree.getRootNode();

}


int main()
{
	bool cont = true;
	int in;
	while(cont)
	{
		cout << "1\n2\n3\n0\n";
		cin >> in;

		switch (in)
		{
		case 1:
			fivehundredtozero();
			break;
		case 2:
			zerotofivehunred();
			break;
		case 3:
			zerotofifty();
			break;
		case 0:
			cont = false;
			break;
		default:
			cout << "Error!!!\n\n";
			break;
		}

	}
	system("pause");
}
