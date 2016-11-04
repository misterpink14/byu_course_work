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


	queryEvaluation(Prog.Queries, Prog.Rules, out);
	//Queries
//	out << "Query Evaluation\n\n";
//	if (Prog.Facts.size() == 0)
//	{
//		for (auto a : Prog.Queries)
//		{
//			out << a.toStr() << "? No\n";
//		}
//		return;
//	}
//	for (auto a : Prog.Queries)
//	{
//		out << a.toStr() << "? ";
//		evaluateQueries(a.Name, a, out);
//		v.clear();
//	}

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

	//out << endl;
}


bool Database::checkEqual(map<int, string> &pos, Relation &r)
{
	
	/*if (pos.size() == 2 && (pos.count(0) + pos.count(1)) == 2 && pos.at(0) == pos.at(1))
	{
		return true;
	}*/
	if(pos.size() > 1)
	{

		auto a = pos.begin();
		a++;
		for (; a != pos.end(); a++)
		{
			if (std::prev(a)->second == a->second)
			{
				r.select(std::prev(a)->first, a->first);
				auto it = a;
				a--;
				pos.erase(it);
			}
		}
	}
	return false;
}


void Database::queryEvaluation(vector<Predicate> &Queries, vector<Rule> &Rules, ofstream &out)
{
	Graph depGraph;

	// build dependency graph
	buildDepGraph(depGraph, Queries, Rules);
	outputDepGraph(depGraph, out);

	// begin query eval
	out << "Query Evaluation\n";
//	if (Facts.size() == 0)
//	{
//		for (auto a : Queries)
//		{
//			out << a.toStr() << "? No\n";
//		}
//		return;
//	}

	int n = 1;
	for (auto a : Queries)
	{
		stringstream ss;
		ss << "Q" << n;
		out << endl << a.toStr() << "?\n\n";

		//Depth-First Search
		int pos = 1;
		dfs(depGraph[ss.str()], depGraph, pos, out);

//		depGraph.output();

		ofstream eatout;
		stack<string> order;
		stack<string> order1;
		Graph depGraph1 = depGraph;
		out << "Postorder Numbers\n  " << ss.str() << ": " << depGraph[ss.str()].PostOrder;
		dfsout(depGraph[ss.str()], depGraph1, eatout, order);
		out << endl;
		map<int, int> position;
		order1 = order;
		// Rule Evaluation Order
		evaluationOrderOut(depGraph, order, out, position);
//		map<int, string> sort;


		out << "\nBackward Edges";

		vector<string> sorted;
		while(!order.empty())
		{
			sorted.push_back(order.top());
			order.pop();
		}

		for(unsigned i = 0; i < sorted.size(); i++)
		{
			for(unsigned j = i+1; j < sorted.size(); j++)
			{
				if (sorted[i] == sorted[j])
				{
					sorted.erase(sorted.begin()+j);
				}
				else if(depGraph[sorted[i]].PostOrder < depGraph[sorted[i]].PostOrder)
				{
					string temp;
					temp = sorted[i];
					sorted[i] = sorted[j];
					sorted[j] = temp;
				}
			}
		}


		bool repeat = false;
		// Backward Edges
		//while(findCycle(depGraph, order))
		findCycle(depGraph, sorted);


		if(sorted.size() > 0)
		{
			repeat = true;
			outputBackEdges(sorted, out);
		}

		// Rule Evaluation
		out << "\n\nRule Evaluation\n";

		vector<Rule> rs;


		buildRules(rs, position, Rules);
//		for(auto p: position)
//		{
//			rs.push_back(Rules[p.second-1]);
//		}

		evaluateRules(out, rs, repeat);

reset(depGraph[ss.str()], depGraph);
//depGraph.output();
		out << endl <<  a.toStr() << "? ";
		evaluateQueries(a.Name, a, out);

		n++;
	}
}

void Database::buildRules(vector<Rule> &rs, map<int, int> &position, vector<Rule> &Rules)
{
	for(auto p: position)
	{
		rs.push_back(Rules[p.second-1]);
	}
}

void Database::buildDepGraph(Graph &depGraph, vector<Predicate> &Queries, vector<Rule> &Rules)
{

	map <string, vector<string>> rname;
	int n = 1;

	for (auto a: Rules)
	{
		stringstream id;
		id << "R" << n;
		Node add;
		add.name = id.str();
		for (auto b: a.Body)
		{
			add.NodeNames.insert(b.Name);
		}

		rname[a.Head.Name].push_back(id.str());
		depGraph.insert(std::pair<string,Node>(id.str(), add));
		n++;

	}
	n = 1;


	renameDepRules(depGraph, rname);
//	for (auto a: depGraph)
//	{
//		set<string> newn;
//		for (auto b: a.second.NodeNames)
//		{
//			if (rname.count(b) != 0)
//			{
//				for (auto c: rname[b])
//				{
//					newn.insert(c);
//				}
//			}
//		}
//		depGraph[a.first].NodeNames.clear();
//		depGraph[a.first].NodeNames = newn;
//	}

	for (auto a: Queries)
	{
		stringstream id;
		id << "Q" << n;
		Node add;
		add.name = id.str();
		if(rname.count(a.Name) != 0)
		{
			for(auto b: rname[a.Name])
			{
				add.NodeNames.insert(b);
			}
		}

		depGraph.insert(std::pair<string,Node>(id.str(), add));
		n++;

	}

}

void Database::renameDepRules(Graph &depGraph, map <string, vector<string>> &rname)
{

	for (auto a: depGraph)
	{
		set<string> newn;
		for (auto b: a.second.NodeNames)
		{
			if (rname.count(b) != 0)
			{
				for (auto c: rname[b])
				{
					newn.insert(c);
				}
			}
		}
		depGraph[a.first].NodeNames.clear();
		depGraph[a.first].NodeNames = newn;
	}
}

void Database::outputDepGraph(Graph &depGraph, ofstream &out)
{
	out << "Dependency Graph\n";
	for (auto a: depGraph)
	{
		out << "  " << a.first << ":";
		for (auto b: a.second.NodeNames)
		{
			out << " " << b;
		}
		out << endl;
	}
	out << endl;
}

void Database::dfs(Node &x, Graph &depGraph, int& pos, ofstream &out)
{

	//mark x visited
	x.visited = true;
	x.PostOrder = 1;


	for(auto y: x.NodeNames)// each node y that is adjacent to node x
	{

		if(depGraph[y].visited == false)// y is not marked
		{
			dfs(depGraph[y], depGraph, pos, out);
			//pos++;
		}
	}

//	cout << "name: " << x.name << " PO: " << pos << endl;
	x.PostOrder = pos;
//	depGraph.output();
	pos++;
//	cout << "      " << x.PostOrder << endl;

//	x.PostOrder = pos;
}

void Database::dfsout(Node &x, Graph &depGraph, ofstream &out, stack<string> &order)
{
	out << x.PostOrder << endl;

	x.visited = false;
	x.PostOrder = 0;

//	pos++;
	for(auto y: x.NodeNames)// each node y that is adjacent to node x
	{

		if(depGraph[y].visited == true)// y is not marked
		{
			order.push(y);
			out << "  " << y << ": ";
			dfsout(depGraph[y], depGraph, out, order);
		}
	}
}

void Database::reset(Node &x, Graph &depGraph)
{
//	x.visited = false;
//	x.PostOrder = 0;

//	pos++;
	for(auto y = depGraph.begin(); y != depGraph.end(); y++)// each node y that is adjacent to node x
	{

//		if(depGraph[y].visited == true)// y is not marked
//		{
	//		reset(depGraph[y], depGraph);
			y->second.visited = false;
			y->second.PostOrder = 0;
//		}
	}
}


bool Database::findCycle(Graph &depGraph, stack<string> &order)
{

	dfsForest(depGraph);

	while(!order.empty())
	{
		string n = order.top();
		string prev = order.top();
		order.pop();
		for(auto a: depGraph[n].NodeNames)
		{
//			cout << "!!! " << a << endl;
			if (depGraph[prev].PostOrder <= depGraph[a].PostOrder)
			{
				order.push(a);
				order.push(prev);
				return true;
			}
			prev = a;
		}
	}
	return false;
//		   for each edge x->y (for each node and for each adjacent node)
//			  if x.postorder <= y.postorder
//				 return true
//			  end if
//		   end for

//		   return false
}

void Database::findCycle(Graph &depGraph, vector<string> &order)
{
//	cout << "findCyc\n";
	dfsForest(depGraph);

	vector<string> neworder;
	for(auto o: order)
	{
//		cout << o << endl;
		string n = o;
		string prev = o;
		for(auto a: depGraph[n].NodeNames)
		{
//			cout << prev << " ;;;; " << a << endl;
//			cout << depGraph[prev].PostOrder <<" ;;;; " << depGraph[a].PostOrder << endl;
			if (depGraph[prev].PostOrder <= depGraph[a].PostOrder)
			{
				neworder.push_back(prev);
				neworder.push_back(a);
				//break;
				continue;
			}
			//prev = a;
		}
	}
	order = neworder;
}

void Database::dfsForest(Graph &depGraph)
{
	int pos = 1;
	ofstream eatout;
	for(auto a: depGraph)// each node x
	{
		if(a.second.visited == false) //node x is not marked
		{
			dfs(a.second, depGraph, pos, eatout);
		}
	//	pos++;
	}
}

void Database::evaluationOrderOut(Graph &depGraph, stack<string> order, ofstream &out, map<int,int> &pos)
{

	set <string> s;
	while(!order.empty())
	{
		s.insert(order.top());
		order.pop();
//		string str = order.top();
////		out << "  " << str << endl;
////		str = ;
//		int i = std::stoi(str.substr(1));
//		pos.insert(std::pair<int,int>(depGraph[str].PostOrder,i));
//		order.pop();
	}
	map<int, string> reorder;
	map<string, int> reorder1;
	for(auto a: s)
	{
		reorder.insert(std::pair<int, string>(depGraph[a].PostOrder,a));
		reorder1.insert(std::pair<string, int>(a,depGraph[a].PostOrder));
	}
	for (auto a = reorder1.begin(); a != reorder1.end(); a++)
	{
		out << "  " << a->first << ": " << a->second << endl;
		order.push(a->first);
	}

	out << "\nRule Evaluation Order\n";
	for (auto a: reorder)
	{
		out << "  " << a.second << endl;
		string str = a.second;
		int i = std::stoi(str.substr(1));
		pos.insert(std::pair<int,int>(depGraph[str].PostOrder,i));
//		order.push(a.);
	}
}

void Database::outputBackEdges(stack<string> &order, ofstream& out)
{
	out << " ";
	for (unsigned i = 0; i < 2; i++)
	{
		out << " " << order.top();
		order.pop();
		if(i == 0)
		{
			out << ":";
		}
	}
	out << "\n";
}


void Database::outputBackEdges(vector<string> &order, ofstream& out)
{
	map<string, vector<string>> theout;
	out << "\n";
//	string key;
	for (unsigned i = 0; i < order.size(); i++)
	{
		if(theout.count(order[i]) == 0)
		{
			vector<string> v;
			v.push_back(order[++i]);
			theout[order[--i]] = v;
			i++;
			continue;
		}
		vector <string> v;
		v = theout.at(order[i]);//.push_back(theout[order[i++]]);
		v.push_back(order[++i]);
		theout[order[--i]] = v;
		i++;
//		out << " " << order[i];
//		out << " " << order[i++];
//		if(i%2 == 0)
//		{
//			out << ":";
//		}
//		order.back();
//		order.pop_back();
	}
unsigned i = 0;
	for(auto a:theout)
	{
		out << "  " << a.first << ":";
		for (auto b:a.second)
		{
			out << " " << b;
		}
		if (theout.size()-1 == i++)
			break;
		out << endl;
	}
}







void Database::evaluateRules (ofstream &out, vector<Rule> &Rules, bool &repeat)
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


				evalRul(strParam, r);
//				evalRul()
//				switch (strParam.size())
//				{
//					case 0:
//						break;
//					default:
//					{
//						for(auto a : strParam)
//						{
//							r.select(a.first, a.second);
//						}
//						break;
//					}
//				}


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


		if(dbsize == size() || !repeat)
		{
			break;
		}
	}

	//out << "\nConverged after " << passes << " passes through the Rules.\n\n";
	//ruleOutput(out);
}

void Database::evalRul(map<int, string> &strParam, Relation &r)
{
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
