#include "DatalogProgram.h"	



//void DatalogProgram::Scheme

void DatalogProgram::Parse(ifstream &in, ofstream &out)
{
	try
	{
		DatalogProgram Prog;
		S.scan(in, out);
		
		// Schemes -> Identifier(PARAMLIST)
		getToken();
		Match(Kind::SCHEMES);
		Match(Kind::COLON);
//		if (t.getK() == Kind::SCHEMES)
//		{
//			getToken();
//			getToken();
//		}
//		else
//		{
//			error();
//		}

		do
		{
			Predicate P;
			Pred(P);
			Schemes.push_back(P);
		}
		while (t.getK() != Kind::FACTS);
		
		// Facts -> Identifier(PARAMLIST).
		Match(Kind::FACTS);
		Match(Kind::COLON);
		
		/*if (t.getK() == Kind::FACTS)
		{
			getToken();
			getToken();
		}
		else
		{
			error();
		}*/
		
		while (t.getK() != Kind::RULES)
		{
			
			Predicate P;
			Pred(P);
			Match(Kind::PERIOD);
			Facts.push_back(P);
		}
		
		
		// Rules -> Identifier(PARAMLIST) :- PREDICATELIST
		Match(Kind::RULES);
		Match(Kind::COLON);
		
		/*if (t.getK() == Kind::RULES)
		{
			getToken();
			getToken();
		}
		else
		{
			error();
		}*/
		while (t.getK() != Kind::QUERIES)
		{
			Rule R;
			Predicate P;
			//R.clear();
			Pred(P);
			
			R.Head = P;
			Match(Kind::COLON_DASH);
			do
			{
				P.ParamList.clear();
				Pred(P);
				R.Body.push_back(P);
				if (t.getK() != Kind::PERIOD)
				{
					Match(Kind::COMMA);
					Perror(t.getK());
					//if (t.getK() == Kind::PERIOD)
					//{
					//	throw t;
					//}
				}
			}
			while (t.getK() != Kind::PERIOD);
			
			Match(Kind::PERIOD);
			Rules.push_back(R);
		}
		// Queries -> Identifier(PARAMLIST) ?
		Match(Kind::QUERIES);
		Match(Kind::COLON);
		/*if (t.getK() == Kind::QUERIES)
		{
			getToken();
			getToken();
		}
		else
		{
			error();
		}*/
		do
		{
			
		//	cout << t.output() << endl;
			Predicate P;
			Pred(P);
			//cout << t.output() << endl;
			Match(Kind::Q_MARK);
			//cout << t.output() << endl;
			Queries.push_back(P);
		}
		while (position < S.tList.size());
		if (t.getK() != Kind::ERROR)
		{
			throw t;
		}
		output(out);
	}
	catch (Token e)
	{
		out << "Failure!\n\t" << e.output() << endl;
	}
}

void DatalogProgram::Pred(Predicate &P)
{
	P.Name = t.getValue();
	Match(Kind::ID);
	Match(Kind::LEFT_PAREN);
	ParamList(P);
	Match(Kind::RIGHT_PAREN);
}


/*
	<ParamList> -> <Param>, <ParamList>
				-> <Param>
	Builds a Parameter List
*/
void DatalogProgram::ParamList(Predicate &P)
{
	Parameter PM;
	Param(P, PM);
	if (t.getK() == Kind::COMMA)
	{
		Match(Kind::COMMA);
		ParamList(P);
	}
}

void DatalogProgram::Perror(Kind k)
{
	if (k == Kind::PERIOD)
	{
		throw t;
	}
}
	
/*
	
*/
void DatalogProgram::Param(Predicate &P, Parameter &PM)
{
//	Parameter PM;
	if (t.getK() == Kind::STRING)
	{
		PM.Value = t.getValue();
		PM.K = t.getK();
		Match(Kind::STRING);
		Values.insert(PM.Value);
	}
	else if (t.getK() == Kind::ID)
	{
		PM.Value = t.getValue();
		PM.K = t.getK();
		Match(Kind::ID);
	}
	else
	{
		error();
	}
	P.ParamList.push_back(PM);
}

void DatalogProgram::error()
{
	throw t;
}

void DatalogProgram::Match(Kind k)
{
	if (k == t.getK())
	{
		getToken();
	}
	else
	{
		error();
	}
}

void DatalogProgram::getToken()
{
	if (position < S.tList.size())
	{
		t = S.tList[position];
		position++;
	}
	else
	{
		t.setK(Kind::ERROR);
	}
}

void DatalogProgram::output(ofstream &out)
{
	out << "Success!\n";

	// Schemes
	out << "Schemes(" << Schemes.size() << "):\n";
	for(auto a: Schemes)
	{
		out << "  " << a.toStr() << endl;
	}
	
	// Facts
	out  << "Facts(" << Facts.size() << "):\n";
	for(auto a: Facts)
	{
		out << "  " << a.toStr() << endl;
	}
	
	// Rules
	out << "Rules(" << Rules.size() << "):\n";
	for(auto a: Rules)
	{
		out << "  " << a.toStr() << endl;
	}
	
	// Queues
	out << "Queries(" << Queries.size() << "):\n";
	for(auto a: Queries)
	{
		out << "  " << a.toStr() << endl;
	}
	
	// STRINGS
	out << "Domain(" << Values.size() << "):\n";
	for(auto a: Values)
	{
		out << "  '" << a << "'\n";
	}
}
