#include "ArenaInterface.h"


		/*
		 *	addFighter(string)
		 *
		 *	Adds a new fighter to the collection of fighters in the arena. Do not allow 
		 *	duplicate names.  Reject any string that does not adhere to the format 
		 *	outlined in the lab specs.
		 *
		 *	Return true if a new fighter was added; false otherwise.
		 */
bool addFighter(string info)
{
	bool add = true;
	string name;
	int hp;
	int str;
	int spd;
	int magic;
	int val = 0;
	while(info[val] != ' ')
	{
		if(val == 0)
			name = info[val];
		else
			name += info[val];
		val++;
	}
	for(int i = 0; i < sizeof(fighters); i++)
	{
		if(fighters[i] == info)
		{
			add = false;
			break;
		}
	}
	if (add == true)
	{
		while(info[val] != ' ')
		{
			string s;
			if(val == 0)
				name = info[val];
			else
				name += info[val];
			val++;
		}
		fighters.push_back(info);
		
	}
	return add;
}

/*
 *	removeFighter(string)
 *
 *	Removes the fighter whose name is equal to the given name.  Does nothing if 
 *	no fighter is found with the given name.
 *
 *	Return true if a fighter is removed; false otherwise.
 */
bool removeFighter(string name)
{
	bool remove = false;
	for(int i = 0; i < sizeof(fighters); i++)
	{
		if(fighters[i] == name)
		{
			remove = true;
			fighters[i] = fighters[(sizeof(fighters)-1)];
			break; 
		}
	}
	if (remove == true)
	{
		fighters.pop_back();
	}
	return remove;
}

/*
 *	getFighter(string)
 *
 *	Returns the memory address of a fighter whose name is equal to the given 
 *	name.  Returns NULL if no fighter is found with the given name.
 *
 *	Return a memory address if a fighter is found; NULL otherwise.
 */
/*FighterInterface* getFighter(string name)
{
	for (int i = 0; i < sizeof(fighters); i++)
	{
		if (name == fighters[i])
		{
			return (&fighters[i]);
		}
	}
}*/
		
		/*
		 *	getSize()
		 *
		 *	Returns the number of fighters in the arena.
		 *
		 *	Return a non-negative integer.
		 */
int getSize()
{
	return sizeof(fighters);
}

