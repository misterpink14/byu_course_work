#include"Relation.h"
#include <iostream>

using std::cout;
using std::endl;


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
			auto it = a.begin();
			for(unsigned i = 0; i < pos; i++)
			{
				it++;
			}
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

void Relation::select(int pos)
{
    set<Tuple> t;
    Tuple tup;
    for (auto a : Tuples)
    {
        tup.push_back (a[pos]);
        t.insert(tup);
        tup.clear();
    }

    Tuples.clear();
	Tuples = t;
}

void Relation::factSelect(int pos, string &value)
{
	set<Tuple> t;
	for (auto a : Tuples)
	{
		if (a[pos] == value)
		{
			auto it = a.begin();
			for(unsigned i = 0; i < pos; i++)
			{
				it++;
			}
			a.erase(it);
			t.insert(a);
		}
	}
	Tuples.clear();
	Tuples = t;
}

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


void Relation::project(map<string, int> &pos)
{
	set<Tuple> newTuples;
	Scheme newSch;
	map<int, int> pos2;

	for (auto a : pos)
	{
		for(unsigned i = 0; i < Sch.size (); i++)
		{
			if (a.first == Sch[i])
			{
				newSch.push_back (Sch[i]);
				pos2.insert (std::pair<int,int>(a.second, i));
				break;
			}
		}
	}

	for (auto a : Tuples)
	{
		Tuple t;
		for (auto b: pos2)
		{
			t.push_back (a[b.second]);
		}
		newTuples.insert (t);
	}

	Tuples.clear();
	Sch.clear();
	Tuples = newTuples;
	Sch = newSch;
}

void Relation::project(map<int, string> &pos)
{
    set<Tuple> newTuples;
    Scheme newSch;
	map<int, int> pos2;

    for (auto a : pos)
    {
		newSch.push_back (a.second);
		for(unsigned i = 0; i < Sch.size (); i++)
		{
				pos2.insert (std::pair<int,int>(a.first, a.first));
				break;
		}
    }

    for (auto a : Tuples)
    {
        Tuple t;
        for (auto b: pos2)
		{
            t.push_back (a[b.second]);
        }
        newTuples.insert (t);
    }

    Tuples.clear();
	Sch.clear();
    Tuples = newTuples;
	Sch = newSch;
}

void Relation::rename(map<int, string> &pos, map<int, string> &strParam)
{
	Scheme newSch;



	for (auto a : pos)
	{
		newSch.push_back (a.second);
	}
	if (strParam.size() > 0)
	{
		map<string, int> removed;
		map<int, string> newpos;
		for(auto a: strParam)
		{
			removed.insert(std::pair<string, int>(a.second, a.first));
		}
		if(removed.size() > 0)
		{
			rr(removed);
//			set<Tuple> ss;
//			for (auto s: Tuples)
//			{
//				Tuple t;
//				for (auto st: s)
//				{
//					if(removed.count(st) > 0)
//					{
//						continue;
//					}
//					t.push_back(st);
//				}
//				ss.insert(t);
//			}
//			Tuples.clear();
//			Tuples = ss;
		}
		int sub = 0;
		for (auto a : pos)
		{
			if(removed.count(a.second) > 0)
			{
				sub++;
				continue;
			}
			newpos.insert(std::pair<int,string>(a.first-sub, a.second));
		}
		pos.clear();
		pos = newpos;
	}

	Sch.clear();
	Sch = newSch;
}

void Relation::rr(map<string,int> &removed)
{
	set<Tuple> ss;
	for (auto s: Tuples)
	{
		Tuple t;
		for (auto st: s)
		{
			if(removed.count(st) > 0)
			{
				continue;
			}
			t.push_back(st);
		}
		ss.insert(t);
	}
	Tuples.clear();
	Tuples = ss;
}


void Relation::FactOutput(ofstream &out)
{
    for (auto a : Tuples)
    {
        out << std::endl;
        out << " ";
        for (unsigned i = 0; i < a.size(); i++)
        {
            out << " " << Sch[i] << "='" << a[i] << "'";

        }
    }
}


void Relation::rename(ofstream &out, bool d)
{
	if(d)
	{
		out << "rename\n";
	}
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

void Relation::addTuple(vector<string> &list)
{
	Tuple t;
	for (auto a : list)
	{
		t.push_back(a);
	}
	Tuples.insert(t);

}

void Relation::addTuples(set<Tuple> &tups, ofstream &out)
{
	out << std::endl;
    set<Tuple> justincase;
    bool replace = false;
    for (auto a : tups)
    {
        if(Tuples.count (a) == 1)
        {
            replace = true;
        }
        else
        {
			out << " ";
			for (unsigned i = 0; i < a.size(); i++)
			{
				out << " " << Sch[i] << "='" << a[i] << "'";
			}
			out << std::endl;
            justincase.insert (a);
        }
        Tuples.insert (a);
    }
//    if (replace)
//	{
//        tups = justincase;
//	}
}

void Relation::addSingleTuples(set<Tuple> &tups, ofstream &out)
{
	out << std::endl;
	set<Tuple> justincase;
	bool replace = false;
	for (auto a : tups)
	{
		if(Tuples.count (a) == 1)
		{
			replace = true;
		}
		else
		{
			out << " ";
			for (unsigned i = 0; i < Sch.size() && i < a.size(); i++)
			{
				out << " " << Sch[i] << "='" << a[i] << "'";
			}
			out << std::endl;
			justincase.insert (a);
		}
		Tuples.insert (a);

	}
//    if (replace)
//	{
//        tups = justincase;
//	}
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

void Relation::output()
{
	cout << Name << std::endl;
	for (auto a : Tuples)
	{
		cout << " ";
		for (unsigned i = 0; i < a.size(); i++)
		{
			cout << " " << Sch[i] << "='" << a[i] << "'";

		}
		cout << std::endl;
	}
	cout << std::endl;
}

void Relation::Reorder(Scheme newOrder)
{
    if (newOrder == Sch)
    {
        return;
    }
    map <int,int> rel;
    unsigned ib = 0;
    unsigned ia = 0;
    for (auto a : Sch)
    {
        ib = 0;
        for( auto b : newOrder)
        {

            if (tolower(a[0]) == tolower(b[0]))
            {
                rel.insert (std::pair<int,int>(ia,ib));
                break;
            }
            ib++;
        }
        ia++;
    }
    Sch.clear ();
    Sch = newOrder;

    set<Tuple> newTup;
    for (auto a: Tuples)
    {
        Tuple add;
        for(auto b:rel)
        {
            add.push_back (a[b.second]);
        }
        newTup.insert (add);
    }
    Tuples.clear();
    Tuples = newTup;

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
