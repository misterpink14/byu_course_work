#include "Database.h"
#include <cctype>



void Database::evaluate(ofstream &out, DatalogProgram & Prog)
{
	vector<string> v;

	//Schemes
	for (auto a : Prog.Schemes)
	{
		for (auto it : a.ParamList)
		{
			v.push_back(it.Value);
		}
		evaluateSchemes(a.Name, v);
		v.clear();
	}

	schemeOutput(out);

	//Facts
	for (auto a : Prog.Facts)
	{
		for (auto it : a.ParamList)
		{
			v.push_back(it.Value);
		}
		evaluateFacts(a.Name, v);
		v.clear();
	}
    factOutput(out);

    out << "Rule Evaluation\n\n";
    evaluateRules (out, Prog.Rules);

	//Queries
	out << "Query Evaluation\n\n";
	if (Prog.Facts.size() == 0)
	{
		for (auto a : Prog.Queries)
		{
			out << a.toStr() << "? No\n";
		}
		return;
	}
	for (auto a : Prog.Queries)
	{
		out << a.toStr() << "? ";
		evaluateQueries(a.Name, a, out);
		v.clear();
	}

}

void Database::evaluateSchemes(string &n, vector<string> &list)
{
	Relation r(n, list);
	Relations.insert(std::pair<string, Relation>(n, r));
}

void Database::schemeOutput(ofstream &out)
{
	out << "Scheme Evaluation\n\n";
}

void Database::evaluateFacts(string &n, vector<string> &list)
{
	Relations[n].addTuple(list);
}

void Database::factOutput(ofstream &out)
{
	out << "Fact Evaluation\n\n";
	for (auto a : Relations)
	{
		a.second.output(out);
    }
}

void Database::evaluateQueries(string &n, Predicate &Query, ofstream &out)
{
	string name = Query.Name;
	map<int,string> pos;
	map<int, string> pos2;
	pos.clear();
	
	for (unsigned i = 0; i < Query.ParamList.size(); i++)
	{
		string str = Query.ParamList[i].toStr();
		if (Query.ParamList[i].K == Kind::STRING)
		{
			pos2.insert(std::pair<int, string>(i, Query.ParamList[i].Value));
			continue;
		}
		pos.insert(std::pair<int, string>(i, Query.ParamList[i].Value));
	}
	Relation r = Relations[name].select();

	if(pos.size() > 1 && checkEqual(pos, r))
	{
		r.select2();
		pos.erase(1);
	}
	else
	{
		for (auto a : pos2)
		{
			r.select(a.first, a.second);
		}
	}
	if (r.Tuples.size() == 0)
	{
		out << "No\n";
	}
	else
	{
		out << "Yes(" << r.Tuples.size() << ")\n";
		r.yesOut(out);

		r.project(out, pos);

		r.rename(out);
	}

	out << endl;
}


bool Database::checkEqual(map<int, string> &pos, Relation &r)
{
	auto del = pos.begin();
	
	if(pos.size() > 1)
	{
		for (auto a = pos.begin(); a != pos.end(); a++)
		{
			for (auto it = ++pos.begin(); it != pos.end(); it++)
			{
				if (a->first != it->first && a->second == it->second)
				{
                    r.select(a->first, it->first);
					del = it;
					it--;
					pos.erase(del);
				}
			}
		}
	}
	
	return false;
}

void Database::evaluateRules (ofstream &out, vector<Rule> &Rules)
{
	map<string, Relation> outr;
    unsigned passes = 0;
    while(1)
    {
        passes++;
        int dbsize = size();

        map<string,int> findSch;

		map<string, int> tempSch;
		map<int, string> pos2;

        for(auto ru: Rules)
		{
			map<string, int> pos;
			bool c = false;
			vector<Relation> variablePoo;
			map<int, string> equal;
            unsigned i = 0;
			unsigned j = 0;
			bool reverse = false;

            for (auto a:ru.Head.ParamList)
            {
				findSch[a.Value] = i;
                i++;
            }
			i = 0;

			out << ru.Head.toStr() << " :- ";
            for (auto b:ru.Body)
			{
				map<int, string> pro;
				insertComma(c, out);
				c = true;
				out << b.toStr();
				i = 0;
				map<int, string> strParam;
                Relation r = Relations[b.Name];
//				reverse = isReverse(ru.Head.ParamList, b.ParamList[0].Value, ru.Head.ParamList[1].Value, b.ParamList[1].Value, ru.Head.ParamList[0].Value);

				ruleBodyAction(b, strParam, i, pro, findSch, equal, j, pos);
//				for (auto a: b.ParamList)
//				{
//					if (a.K == Kind::STRING)
//					{
//						strParam.insert(std::pair<int, string>(i, a.Value));
//						continue;
//					}
//					pro.insert(std::pair<int, string>(i, a.Value));
//					if(findSch.count (a.Value) > 0)
//					{
//						pos.insert (std::pair<int,string>(j, a.Value));
//					}
//					equal.insert(std::pair<int,string>(j, a.Value));
//                    i++;
//					j++;
//                }


				switch (strParam.size())
				{
					case 0:
						break;
					default:
					{
						for(auto a : strParam)
						{
							r.select(a.first, a.second);
						}
						break;
					}
				}
//				if (strParam.size () > 0)
//				{
//					for(auto a : strParam)
//					{
//						r.select(a.first, a.second);
//					}
//				}


				r.rename(pro, strParam);
		//		r.output();

				variablePoo.push_back(r);
			}

			ruleAction(variablePoo, reverse, out, equal, findSch, ru, pos);

//			if( variablePoo.size() == 1 )
//			{
//				if (reverse)
//				{
//					set<Tuple> s;
//					for(auto a : variablePoo[0].Tuples)
//					{
//						Tuple t;
//						t.push_back(a[1]);
//						t.push_back(a[0]);
//						s.insert(t);
//					}
//					Relations[ru.Head.Name].addTuples(s, out);
//				}
//				else
//				{
//					Relations[ru.Head.Name].addSingleTuples(variablePoo[0].Tuples, out);
//				}
//			}
//			else
//			{
//				join(variablePoo,equal);
//				variablePoo[0].project(findSch);

//				// AddTuples or add line
//				if(variablePoo.size() == 1)
//				{
//					Relations[ru.Head.Name].addTuples(variablePoo[0].Tuples, out);
//				}
//				else
//				{
//					out << endl;
//				}
//			}

			// Cleanup
			pos.clear();
			findSch.clear();
			variablePoo.clear();
		}


        if(dbsize == size())
        {
            break;
        }
    }

	out << "\nConverged after " << passes << " passes through the Rules.\n\n";
	ruleOutput(out);
}

void Database::sort(vector<Relation> &rels, vector<string> &newOrder)
{
    for (unsigned i = 0; i < newOrder.size(); i++)
    {
        if (rels[i].Sch[0] != newOrder[i])
        {
            for(unsigned k = i; i < rels.size(); i++)
            {
                if(rels[k].Sch[0] == newOrder[i])
                {
                    Relation temp;
                    temp = rels[i];
                    rels[i] = rels[k];
                    rels[k] = temp;
                }
            }
        }
    }
}

string Database::toUpper (string val)
{
    for (unsigned i = 0; i < val.size(); i++)
    {
        val[i] = toupper(val[i]);
    }
    return val;
}

string Database::toLower (string val)
{
    for (unsigned i = 0; i < val.size(); i++)
    {
        val[i] = tolower(val[i]);
    }
    return val;
}

void Database::insertComma(bool& c, ofstream &out)
{
	if (c)
	{
		out << ",";
	}
}

void Database::insertComma (bool &doit, bool &doit2, ofstream &out, string output)
{
	if(doit && doit2)
    {
        out << "," << output;
    }
    else if(doit2)
    {
        out << output;
    }
}

void Database::ruleOutput (ofstream &out)
{
	for (auto a : Relations)
	{
		a.second.output(out);
	}
}

// Make a Scheme for the result relation
void Database::makeSch(Relation &rel1, Relation &rel2, Scheme &s)
{
	s = rel1.Sch;

//	for(unsigned i = 1; i < rels.size(); i++)
//	{
		for(auto n : rel2.Sch)
		{
			if (count(s.begin(), s.end(), n) == 0)
			{
				s.push_back(n);
			}
		}
//	}
}

bool Database::joinable(Tuple &t1, Tuple &t2, Scheme &sc1, Scheme &sc2)
{

    if(t1.size() == 0 || t2.size() == 0)
    {
        return false;
	}
	for (unsigned a = 0; a < sc1.size(); a++)
	{
		for (unsigned b = 0; b < sc2.size(); b++)
        {
			if (sc1[a] == sc2[b] && t1[a] != t2[b])
			{
                return false;
			}
		}
    }
    return true;
}


void Database::join(vector<Relation> &rels, map<int, string> &equal)
{

	set<Tuple> s;
	unsigned i = 1;
	while(rels.size() > 1)
	{
		Scheme sh;
		makeSch(rels[0], rels[i], sh);

		for(auto t1: rels[0].Tuples)
		{
			for(auto t2: rels[i].Tuples)
			{
				if (joinable(t1, t2, rels[0].Sch, rels[i].Sch))
				{
					Tuple t = makeTuple(t1, t2, rels[0].Sch, rels[i].Sch, equal);
					if (t.size() > 0)
					{
						s.insert(t);
					}
				}
			}

		}
		rels[0].Sch.clear();
		rels[0].Sch = sh;
//		rels[0].output();
//		i++;
		rels[0].Tuples.clear();

		rels[0].Tuples = s;
		s.clear();
		rels.erase(rels.begin()+1);

	}
}

Tuple Database::makeTuple(Tuple &t1, Tuple &t2, Scheme &s1, Scheme &s2, map<int,string> &equal)
{
	Tuple t = t1;
	for(unsigned i = 0; i < s2.size(); i++)
	{
		if(count(s1.begin(), s1.end(), s2[i]) == 0)
		{
			t.push_back(t2[i]);
		}
	}

	return t;
}


int Database::size()
{
    int s = Relations.size();
    for(auto a:Relations)
    {
        s+=a.second.Tuples.size();
    }
    return s;
}

bool Database::isReverse(vector<Parameter> &h, string &b0, string &ru1, string &b1, string &ru0)
{
	if(h.size() == 2 && b0 == ru1 && b1 == ru0)
	{
		return true;
	}
}

void Database::ruleAction(vector<Relation> &variablePoo, bool &reverse, ofstream &out, map<int, string> &equal, map<string, int> & findSch, Rule &ru, map<string, int> &pos)
{
	if( variablePoo.size() == 1 )
	{
		if (reverse)
		{
			set<Tuple> s;
			for(auto a : variablePoo[0].Tuples)
			{
				Tuple t;
				t.push_back(a[1]);
				t.push_back(a[0]);
				s.insert(t);
			}
			Relations[ru.Head.Name].addTuples(s, out);
		}
		else
		{
			variablePoo[0].project(findSch);
			Relations[ru.Head.Name].addTuples(variablePoo[0].Tuples, out);
		}
	}
	else
	{
		join(variablePoo,equal);
		variablePoo[0].project(findSch);

		// AddTuples or add line
		if(variablePoo.size() == 1)
		{
			Relations[ru.Head.Name].addTuples(variablePoo[0].Tuples, out);
		}
		else
		{
			out << endl;
		}
	}
}


void Database::ruleBodyAction(Predicate &b, map<int, string> &strParam, unsigned &i, map<int,string> &pro, map<string, int>&findSch, map<int, string> &equal, unsigned &j, map<string, int> &pos)
{
	for (auto a: b.ParamList)
	{
		if (a.K == Kind::STRING)
		{

			strParam.insert(std::pair<int, string>(i, a.Value));
			continue;
		}
		pro.insert(std::pair<int, string>(i, a.Value));
		if(findSch.count (a.Value) > 0)
		{
			pos.insert (std::pair<string, int>(a.Value, j));
		}
		equal.insert(std::pair<int,string>(j, a.Value));
		i++;
		j++;
	}
//	if(strParam.size() > 0)
//	{
//		for (auto a: findSch)
//		{
//			int i = a.second;
//			for (auto b: strParam)
//			{
//				if(b.)
//			}
//		}
//	}
}

