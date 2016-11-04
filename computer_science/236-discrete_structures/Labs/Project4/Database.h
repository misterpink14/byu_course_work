#ifndef DATABASE_H_
#define DATABASE_H_

#include "DatalogProgram.h"
#include "Relation.h"
#include <map>
#include <algorithm>


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

    void evaluateRules(ofstream &out, vector <Rule> &Rules);

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

public:
	Database() {};

	void evaluate(ofstream &out, DatalogProgram & Prog);

};

#endif
