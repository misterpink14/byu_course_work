/*
 * Mimic.h
 *
 *  Created on: Jun 10, 2014
 *      Author: misterpink14
 */

#ifndef MIMIC_H_
#define MIMIC_H_
#include "MimicInterface.h"
#include <sstream>
#include <cstdlib>
#include <ctime>



class Mimic : public MimicInterface
{
private:

	struct Node
	{
		string key;
		vector<string> value;
		Node* next;

		Node() //: key(""), next(NULL)
		{
			key = "";
			next = NULL;
			value.clear();
		};
		~Node(){}

	};

	Node* head;




	void find(Node*& n, string key)
	{
		n = head;
		while (n != NULL)
		{
			if (key == n->key)
			{
				return;
			}
			n = n->next;
		}
	}

	string random(vector<string> v)
	{

		unsigned int r = rand() % v.size();
		return v[r];
	}



	public:
		Mimic()
		{
			head = NULL;
		}
		~Mimic(){}

		//Part 1--------------------------------------------------------------
		/**
		 * createMap
		 *
		 * Creates a prefix-suffix map based on the input text.
		 *
		 * Go through the input text and examine each group of 3 words. Refer
		 * to the first two words as the "prefix" and the third word as the
		 * "suffix". Create a map that associates each prefix with each suffix.
		 *  If you encounter a prefix that has been read already, add the new
		 *  suffix to the list of suffixes already associated with that prefix;
		 *  in this manner, each prefix can be associated with multiple
		 *  suffixes and even multiple copies of the same suffix. Note that
		 *  the input texts will only contain words separated by spaces.  Also
		 *  note that the last two word prefix in the text should be associated
		 *  with the suffix "THE_END".
		 *
		 * @param input
		 * 		the sample text to be mimicked
		 */
		void createMap(string input)
		{
			srand(time(NULL));
			stringstream ss;
			ss << input;
			string key1;
			string key2;
			string value;
			Node* n;


			ss >> key1;
			ss >> key2;
			while (ss >> value)
			{

				if(head == NULL)
				{
					Node* p = new Node;
					p->key = key1 + " " + key2;
					p->value.push_back(value);
					head = p;
				}
				else
				{
					string key = (key1 + " " + key2);
					n = head;
					while(n->next != NULL)
					{

						if(n->key == key)
						{
							n->value.push_back(value);
							break;
						}
						n = n->next;
					}
					if(n->key == (key))
					{
						n->value.push_back(value);
					}
					else
					{
						n->next = new Node();//(key, value);
						n->next->key = (key);
						n->next->value.push_back(value);
					}
				}

				key1 = key2;
				key2 = value;
			}
			n = head;
			while(n->next != NULL)
			{
				if(n->key == (key1 + " " + key2))
				{
					n->value.push_back("THE_END");
					break;
				}
				n = n->next;
			}
			if(n->key == (key1 + " " + key2))
			{
				n->value.push_back("THE_END");

			}
			else
			{
				n->next = new Node();//(key, value);
				n->next->key = (key1 + " " + key2);
				n->next->value.push_back("THE_END");
			}
		}

		/**
		 * getSuffixList
		 *
		 * Returns the list of suffixes associated with the given prefix.
		 * Returns an empty vector if the given prefix is not in the map or no
		 * map has been created yet.
		 *
		 * @param prefix
		 * 		the prefix to be found
		 * @return a list of suffixes associated with the given prefix if the
		 * 		prefix is found; an empty vector otherwise
		 */
		vector<string> getSuffixList(string prefix)
		{

			vector<string> ret;
			if (head == NULL)
			{
				return ret;
			}
			Node* n = head;
			while (n != NULL)
			{
				if(prefix == n->key)
				{
					return n->value;
				}
				n=n->next;
			}
			return ret;
		}

		//Part 2--------------------------------------------------------------
		/**
		 * generateText
		 *
		 * Generates random text using the map created by the createMap method.
		 *
		 * To generate the new text, start with the first prefix that was read
		 * and randomly select one of the suffixes associated with that prefix.
		 * The next prefix is the second word from the previous prefix and the
		 * selected suffix. Continue selecting random suffixes and building the
		 * next prefix until the suffix "THE_END" is selected. The token
		 * "THE_END" should not be returned as part of your generated text.
		 *
		 * @return random text generated using the map created with the sample
		 * 		text; an empty string if no map has been created yet
		 */
		string generateText()
		{
			if (head == NULL)
			{
				return "";
			}
			stringstream out;
			Node* n = head;
			out << head->key;
			while(n!=NULL)
			{
				string value = n->value[rand() % n->value.size()];
				string key2;

				if (value == "THE_END")
				{
					break;
				}
				out << " " << value;
				stringstream ss(n->key);
				ss >> key2;
				ss >> key2;
				find(n, key2 + " " + value);
			}
			return out.str();
		}
};



#endif /* MIMIC_H_ */
