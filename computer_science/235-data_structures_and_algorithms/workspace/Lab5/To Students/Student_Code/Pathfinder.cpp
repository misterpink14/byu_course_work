/*
 * Pathfinder.cpp
 *
 *  Created on: May 26, 2014
 *      Author: misterpink14
 */

#include "Pathfinder.h"


	// my maze
string Pathfinder::getMaze()
{

	if(it.size() > 0)
	{///figure out how to return it
		stringstream out;
		for (unsigned z = 0; z < d; z++)
		{
			for (unsigned y = 0; y < d; y++)
			{
				for (unsigned x = 0; x < d; x++)
				{
					out << it[x][y][z] << " ";
				}
				out << endl;
			}
			out << endl;
		}
		return out.str();
	}
	else
	{
		stringstream ret;
		for (unsigned x = 0; x < d; x++)
		{
			for (unsigned y = 0; y < d; y++)
			{
				for (unsigned z = 0; z < d; z++)
				{
					ret << "1 ";
				}
				ret << endl;
			}
			ret << endl;
		}
		return ret.str();
	}
}


	// create my maze
void Pathfinder::createRandomMaze()
{

//	srand(std::time(0));
	vector<vector<vector<int> > > temp (5,vector<vector<int> >(5,vector <int>(5,1)));
	for (unsigned z = 0; z < d; z++)
	{
		for (unsigned y = 0; y < d; y++)
		{
			for (unsigned x = 0; x < d; x++)
			{
				temp[x][y][z] = (rand() % 2);
			}
		}
	}
	temp[0][0][0] = 1;
	temp[4][4][4] = 1;
	it = temp;
}



//*******************


bool Pathfinder::importMaze(string file_name)
{

	stringstream values;
	int value = 0;;
	int in;

	ifstream file(file_name.c_str());
	if(file.is_open())
	{
		while( file >> in )
		{
			if( in == 1 || in == 0 )
			{
				value++;
				values << in << " ";
			}
			else
			{
				return false;
			}
		}
		if(value != 125)
		{
			return false;
		}
		file.close();
	}
	else
	{
		return false;
	}

	vector<vector<vector<int> > > temp (5,vector<vector<int> >(5,vector <int>(5)));

	for(unsigned z = 0; z < d; z++)
	{
		for (unsigned y = 0; y < d; y++)
		{
			for (unsigned x = 0; x < d; x++)
			{
				values >> in;
				temp[x][y][z] = in;
			}
		}
	}
	if(values >> in)
	{
		return false;
	}
	if (temp[0][0][0] == 0 || temp[4][4][4] == 0)
	{
		return false;
	}
	it = temp;
	return true;
}



//*******************


vector<string> Pathfinder::solveMaze()
{
	solve = it;
	path.clear();
	path.push_back(tostr(0,0,0));
	if(recursion(0,0,0))
	{
		return path;
	}
	else
	{
		vector<string> no;
		return no;
	}
}
