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
    Relation(string n, vector<string> &list) : Name(n)
	{
		for (auto a : list)
		{
			Sch.push_back(a);
		}
	}
	Relation(string n, Scheme list) : Name(n), Sch(list) {}
	Relation select();
	void select(int pos, string &value);
	void select2();
	void select(int pos1, int pos2);
    void select(int pos);
	void factSelect(int pos, string &value);
    void Reorder(Scheme newOrder);
	void project(ofstream &out, map<int, string> &pos);
	void project(map<string, int> &pos);
    void project(map<int, string> &pos);
	void rename(ofstream &out, bool d = true);
	void rename(map<int, string> &pos,map<int, string> &strParam);
    void addTuple(vector<string> &list);
	void addSingleTuples(set<Tuple> &tups, ofstream &out);
	void addTuples(set<Tuple> &tups, ofstream &out);
    void FactOutput(ofstream &out);
	void output(ofstream &out);
	void output();
	void yesOut(ofstream &out);
	void rr(map<string,int> &removed);
};

#endif
