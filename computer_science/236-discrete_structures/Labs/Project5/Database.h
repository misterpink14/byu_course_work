#ifndef DATABASE_H_
#define DATABASE_H_

#include "DatalogProgram.h"
#include "Relation.h"
#include "Graph.h"
#include <map>
#include <algorithm>
#include <stack>

using std::stack;


using std::map;

class Database
{
	map<string, Relation> Relations;

	// Scheme Name,
	void evaluateSchemes( string &n, vector<string> &list );

	void schemeOutput( ofstream &out );

	void evaluateFacts( string &name, vector<string> &list );

	void factOutput(ofstream &out);

	void evaluateQueries(string &n, Predicate &Query, ofstream &out);

	void evaluateRules(ofstream &out, vector <Rule> &Rules, bool &repeat);

	void insertComma(bool &c, ofstream &out);

	void insertComma(bool &doit, bool &doit2, ofstream &out, string output);

	void ruleOutput(ofstream &out);

	void sort(vector<Relation> &rels, vector<string> &newOrder);

	void makeSch(Relation &rel1, Relation &rel2, Scheme &s);

	Tuple makeTuple(Tuple &t1, Tuple &t2, Scheme &s1, Scheme &s2, map<int, string> &equal);

	string toUpper (string val);
	string toLower (string val);

	/*
	 * JOIN
	 *
	 * 1-Join 2 relations that have no common attributes (cartesian product)
	 * 2-join 2 relations w/ multiple common attributes
	 *
	 * */

	void join(vector<Relation> &rels, map <int, string> &equal);

	bool joinable(Tuple &t1, Tuple &t2, Scheme &sc1, Scheme &sc2);

	void queriesOutput(ofstream &out);

	bool checkEqual(map<int, string> &pos, Relation &r);

	int size();

	bool isReverse(vector<Parameter> &h, string &b0, string &ru1, string &b1, string &ru0);

	void ruleAction(vector<Relation> &variablePoo, bool &reverse, ofstream &out, map<int, string> &equal, map<string, int> & findSch, Rule &ru, map<string, int> &pos);

	void ruleBodyAction(Predicate &b, map<int, string> &strParam, unsigned &i, map<int,string> &pro, map<string, int>&findSch, map<int, string> &equal, unsigned &j, map<string, int> &pos);


	void queryEvaluation(vector<Predicate> &Queries, vector<Rule> &Rules, ofstream &out);

	void buildDepGraph(Graph &depGraph, vector<Predicate> &Queries, vector<Rule> &Rules);

	void renameDepRules(Graph &depGraph, map <string, vector<string>> &rname);

	void outputDepGraph(Graph &depGraph, ofstream &out);

	void dfs(Node &x, Graph &depGraph, int& pos, ofstream &out);

	void dfsout(Node &x, Graph &depGraph, ofstream &out, stack<string> &order);

	void reset(Node &x, Graph &depGraph);

	bool findCycle(Graph &depGraph, stack<string> &order);

	void dfsForest(Graph &depGraph);

	void evaluationOrderOut(Graph &depGraph, stack<string> order, ofstream &out, map<int,int> &pos);

	void outputBackEdges(stack<string> &order, ofstream& out);

	void findCycle(Graph &depGraph, vector<string> &order);

	void outputBackEdges(vector<string> &order, ofstream& out);

	void evalRul(map<int, string> &strParam, Relation &r);

	void buildRules(vector<Rule> &rs, map<int, int> &position, vector<Rule> &Rules);

public:
	Database() {};

	void evaluate(ofstream &out, DatalogProgram & Prog);

};

#endif
