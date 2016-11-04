#ifndef DATALOGPROGRAM_H_
#define DATALOGPROGRAM_H_




#include "Scanner.h"
#include "Predicate.cpp"
#include "Rule.cpp"
#include "Parameter.cpp"
#include <set>
using std::set;


class DatalogProgram
{
public:
	vector <Predicate> Schemes;	// Holds all the Schemes for the Grammar
	vector <Predicate> Facts;	// Holds all the Facts/Applications of Schemes for the Grammar
	vector <Rule> Rules;		// Holds all the Rules for the Grammar
	vector <Predicate> Queries;	// Holds all the Queries for the Grammar
	set <string> Values;
	Scanner S;
	Token t;
	int position;

	DatalogProgram() : position(0) {}

	void Parse(ifstream &in, ofstream &out);

	void Pred(Predicate &P);
	
	void Param(Predicate &P, Parameter &PM);
	
	void ParamList(Predicate &P);

	void error();

	void Match(Kind k);

	void getToken();
	
	void output(ofstream &out);
	
	void Perror(Kind k);

};


#endif 
