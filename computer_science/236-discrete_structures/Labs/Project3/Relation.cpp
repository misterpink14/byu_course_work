#include"Relation.h"
#include <iostream>

using std::cout;


Relation Relation::select()//(vector<int> pos1, vector<int> pos2)
{
	return *this;
}

void Relation::select(int pos, string &value)
{
	set<Tuple> t;
	for (auto a : Tuples)
	{
		if (a[pos] == value)
		{
			t.insert(a);
		}
	}
	Tuples.clear();
	Tuples = t;
}
void Relation::select(int pos1, int pos2)
{
	set<Tuple> t;
	for (auto a : Tuples)
	{
		if (a[pos1] == a[pos2])
		{
			t.insert(a);
		}
	}

	Tuples.clear();
	Tuples = t;
}

/*Relation Relation::select(int position)
{
	Relation r(Name, Sch);
	for (auto a : Tuples)
	{
		r.Tuples.insert(a);
	}
	return r;
}*/

//Relation Relation::select(int position, string value)
//{
//	Relation r(Name, Sch);
//	for (auto a : Tuples)
//	{
//		if (a[] == value)
//		{
//			r.Tuples.insert(a);
//		}
//	}
//	return r;
//}
//
//Relation Relation::select(string value, int position)
//{
//	Relation r(Name, Sch);
//	for (auto a : Tuples)
//	{
//		if (a[0] == value)
//		{
//			r.Tuples.insert(a);
//		}
//	}
//	return r;
//}
//
//Relation Relation::select(int position1, int position2)
//{
//	return *this;
//}
//
//Relation Relation::select(string value1, string value2)
//{
//	Relation r(Name, Sch);
//	for (auto a : Tuples)
//	{
//		if (a[0] == value1 && a[1] == value2)
//		{
//			r.Tuples.insert(a);
//		}
//	}
//	return r;
//}

void Relation::select2()
{
	set<Tuple> t;
	for (auto a : Tuples)
	{
		if (a[0] == a[1])
		{
			t.insert(a);
		}
	}
	Tuples.clear();
	Tuples = t;
}

void Relation::project(ofstream &out, map<int, string> &pos)
{
	set<Tuple> newTuples;
	Scheme newSch;
	bool flag = true;
	out << "project\n";

	for (auto a : Tuples)
	{
		Tuple t;
		if (pos.size() > 0)
		{
			out << " ";
		}
		
		for (auto it : pos)
		{
			if (flag)
			{ 
				newSch.push_back(it.second);
			}
			t.push_back(a[it.first]);
			out << " " << Sch[it.first] << "='" << a[it.first] << "'";
		}
		if (pos.size() > 0)
		{
			newTuples.insert(t);
			out << std::endl;
		}
		flag = false;
	}

	Tuples.clear();
	Sch.clear();
	Tuples = newTuples;
	Sch = newSch;
}

void Relation::rename(ofstream &out)
{
	out << "rename\n";
	for (auto a : Tuples)
	{
		out << " ";
		for (unsigned i = 0; i < a.size(); i++)
		{
			out << " " << Sch[i] << "='" << a[i] << "'";

		}
		out << std::endl;
	}
}

void Relation::addTuple(vector<string> list)
{
	Tuple t;
	for (auto a : list)
	{
		t.push_back(a);
	}
	Tuples.insert(t);

}

void Relation::output(ofstream &out)
{
	out << Name << std::endl;
	for (auto a : Tuples)
	{
		out << " ";
		for (unsigned i = 0; i < a.size(); i++)
		{
			out << " " << Sch[i] << "='" << a[i] << "'";

		}
		out << std::endl;
	}
	out << std::endl;
}


void Relation::yesOut(ofstream &out)
{
	out << "select\n";
	for (auto a : Tuples)
	{
		out << " ";
		for (unsigned i = 0; i < a.size(); i++)
		{
			out << " " << Sch[i] << "='" << a[i] << "'";

		}
		out << std::endl;
	}

}
