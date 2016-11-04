#ifndef RULE_CPP_
#define RULE_CPP_


#include "Predicate.cpp"


class Rule
{
public:
	Predicate Head;
	vector<Predicate> Body;
	
	Rule(){}

	Rule(Predicate pred, vector<Predicate> l) : Head(pred), Body(l){}

	string toStr()
	{
		string ret;
		ret += Head.toStr() + " :- ";
		for (unsigned i = 0; i < Body.size(); i++)
		{
			ret += Body[i].toStr();
			if ( i != Body.size()-1)
			{
				ret += ",";
			}
		}
		return ret;
	}
	
	void clear()
	{
		Body.clear();
	}

};


#endif
