#ifndef SCHEME_H_
#define SCHEME_H_

#include "Scheme.h"
#include "Tuple.h"
#include <set>
#include <map>
#include <fstream>
#include <sstream>

using std::set;
using std::ofstream;
using std::map;

class Relation
{
public:
	string Name;
	Scheme Sch;
	set<Tuple> Tuples;
	Relation(){};
	Relation(string n, vector<string> list) : Name(n) 
	{
		for (auto a : list)
		{
			Sch.push_back(a);
		}
	}
	Relation(string n, Scheme list) : Name(n), Sch(list) {}
	Relation select();
	void select(int pos, string &value);
//	Relation select(int position);
	void select2();
	void Relation::select(int pos1, int pos2);
//	Relation select(int position, string value);
	/*Relation select(string value, int position);
	Relation select(int position1, int position2);
	Relation select(string value1, string value2);*/
	//Relation select();
	void project(ofstream &out, map<int, string> &pos);
	void rename(ofstream &out);
	void addTuple(vector<string> list);
	void output(ofstream &out);
	void yesOut(ofstream &out);
};

#endif
