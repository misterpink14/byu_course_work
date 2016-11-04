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

};

#endif
