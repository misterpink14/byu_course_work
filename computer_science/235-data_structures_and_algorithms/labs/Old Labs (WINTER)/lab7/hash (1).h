#include "linkedlist.h"
#include <string>

using std::endl;
using std::cout;
using std::string;

#pragma once

template <typename ItemType>

class Hash
{
private:
	LinkedList<ItemType> *front[];		//bucket
	unsigned int size;					//size
	unsigned int count;					//count


public:
//	seems legit
	Hash()
	{
		size = 0;
		count = 0;
		front[size] = NULL;
	}
	

	void Add(string &item)
	{
		if(Find(item) != -1)
			return;
		if (count+1 > size)
			Hashing(true);
		unsigned int t = hashCode(item);
		int k = front[t]->size();
		if (k == NULL)
			k = 0;
		front[t]->Insert(k,item);
		//hashCode
		//add to end of bucket
	}

	void Remove(string &item)
	{
		//hashCode for index
		//remove if there
		if (count < size/2)
			Hashing(false);
	}

//	seems legit
//	int Find(string &item)
//	{
//		unsigned int index = hashCode(item);
//		return front[index]->Find(item);
//	}

//	seems legit
	unsigned int hashCode(const string &item)
	{
		unsigned int index = 0;
		cout << "no\n";
		for(unsigned i = 0; i < item.size(); i++)
			index = index * 31 + (unsigned int)(item[i]);
		cout << index;
//		index = index % size;
		return index;
	}

	void Hashing(bool longer)
	{
		unsigned int newsize;
		int zero = 0;
		if(longer)
		{
			newsize = (size * 2 + 1);
		}
		else
		{
			newsize = size / 2;
		}
		LinkedList<ItemType> *n = (*front);
		LinkedList<ItemType> *mew = new LinkedList<ItemType>[newsize];
		front[newsize] = mew;
		ItemType item;
		unsigned int t;
		for (unsigned int i = 0; i < size; i++)
		{
			if( n = NULL )
				continue;
			item = n[i].Remove(zero);
			Add(item);
			/*if(front[i]->size() > 0)
				item = n[i]->Remove(zero);
			else 
				continue;
			t = hashCode(item);
			n[t]->Add(n[t].size(), item);*/
		}
		delete[] n;
		//front = n;
		// new array
		// foreach item
		// hashfunction
	}


};
