#include "Database.h"


void Database::evaluate(ofstream &out, DatalogProgram & Prog)
{
	//out << "\tEVALUATE\n\n*********************\n\n\n";

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
	//vector<string> params;
	
	for (unsigned i = 0; i < Query.ParamList.size(); i++)
	{
		string str = Query.ParamList[i].toStr();
	//	params.push_back(Query.ParamList[i].Value);
		if (Query.ParamList[i].K == Kind::STRING)
		{
			pos2.insert(std::pair<int, string>(i, Query.ParamList[i].Value));
			continue;
		}


		//if (pos.size() == 0)
		//{
			//pos[i] = Query.ParamList[i].Value;
			pos.insert(std::pair<int, string>(i, Query.ParamList[i].Value));
	//	}
	//	else if (i > 0 && Query.ParamList[i].Value != pos[0])
	//	{
	//		pos.insert(std::pair<int, string>(i, Query.ParamList[i].Value));
	//	}
	}
	
	Relation r = Relations[name].select();
	//switch (pos.size())
	//{
	//case 0:		// string,string
	//	if (params.size() == 1)
	//	{
	//		r = Relations[name].select(params[0], 1);
	//		break;
	//	}
	//	r = Relations[name].select(params[0], params[1]);
	//	break;
	//case 1:		// pos,string or string,pos
	//	if ( params.size() > 1 && params[0] == params[1])
	//	{
	//	//	pos[1] = pos[0];
	//		r = Relations[name].select();
	//	}
	//	else if (params.size() == 1)
	//	{
	//		r = Relations[name].select(0);
	//	}
	//	else if (pos.count(0) == 0)
	//	{
	//		r = Relations[name].select(params[0], 1);
	//	}
	//	else
	//	{
	//		r = Relations[name].select(0, params[1]);
	//	}
	//	break;
	//case 2:		// pos,pos
	//	r = Relations[name].select(0, 1);
	//	break;
	//}
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
	
	/*if (pos.size() == 2 && (pos.count(0) + pos.count(1)) == 2 && pos.at(0) == pos.at(1))
	{
		return true;
	}*/
	if(pos.size() > 1)
	{
		cout << "ok" << endl;
		auto a = pos.begin();
		a++;
		for (; a != pos.end(); a++)
		{
			cout << a->second << " " << a->second << endl;
			if (std::prev(a)->second == a->second)
			{
				cout << a->second << " " << a->second << endl;
				r.select(std::prev(a)->first, a->first);
				auto it = a;
				a--;
				pos.erase(it);
			}
		}
	}
	return false;
}


