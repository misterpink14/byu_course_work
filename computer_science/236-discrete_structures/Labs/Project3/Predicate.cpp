#ifndef PREDICATE_CPP_
#define PREDICATE_CPP_


#include "Parameter.cpp"
#include <vector>

using std::vector;

class Predicate
{
public:
	string Name;
	vector <Parameter> ParamList;

	Predicate() {}

	Predicate(string v) : Name(v) {}
	
	string toStr()
	{
		string out;
		out += Name + "(";
		for (unsigned i = 0; i < ParamList.size(); i++)
		{
			out += ParamList[i].toStr();
			if ( i != ParamList.size()-1)
			{
				out += ",";
			}
		}
		return out + ")";
	}

	vector <string> stringifyList()
	{
		vector <string> list;
		for (auto a : ParamList)
		{
			list.push_back(a.Value);
		}
		return list;
	}

	void stringifyList( vector <string> &list)
	{
		for (auto a : ParamList)
		{
			list.push_back(a.Value);
		}
	}

};

#endif
