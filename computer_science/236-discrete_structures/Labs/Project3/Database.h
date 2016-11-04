#ifndef DATABASE_H_
#define DATABASE_H_

#include "DatalogProgram.h"
#include "Relation.h"
#include <map>

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

	void queriesOutput(ofstream &out);
	
	bool checkEqual(map<int, string> &pos, Relation &r);

public:
	Database() {};

	void evaluate(ofstream &out, DatalogProgram & Prog);

};

#endif
