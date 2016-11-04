/*
* @author Benjamin Thompson
* @title Project 1
* @class CS 236
*
*	SCANNER
*		Write a scanner that reads a sequence of characters from a text file, 
*		identifies the datalog language tokens found in the file, and outputs 
*		each token to an output file.
*/

#include "Scanner.h"

Scanner::Scanner() : amt(0) {}


void Scanner::scan( ifstream &in, ofstream &out )
{
	char c;
	string token;
	int line = 1;
	Token t;
	stringstream ss;

	while ( in.get( c ) )
	{
		token = "";
		if ( space(c, line) )
		{
			continue;
		}

		try
		{
			ss.str(std::string());
			ss << c;
			switch (c)
			{
				case '#':
				{
					getline(in, token);
					line++;
					continue;
				}
				case ',':
				{
					t.setAll(COMMA, ss.str(), line);
					break;
				}
				case '.':
				{
					t.setAll(PERIOD, ss.str(), line);
					break;
				}
				case '?':
				{
					t.setAll(Q_MARK, ss.str(), line);
					break;
				}
				case '(':
				{
					t.setAll(LEFT_PAREN, ss.str(), line);
					break;
				}
				case ')':
				{
					t.setAll(RIGHT_PAREN, ss.str(), line);
					break;
				}
				case ':':
				{
					
					if (in.peek() == '-')
					{
						in >> c;
						ss << c;
						t.setAll(COLON_DASH, ss.str(), line);
						break;
					}
					t.setAll(COLON, ss.str(), line);
					break;

				}
				case '\''://string
				{
					t.setAll(STRING, scanString(in), line);
					break;
				}
				default:// Schemes, Facts, Rules, Queries, Id
				{
					Kind k = scanIdent( c, in, token );
					t.setAll( k, token, line );
					space(c, line);
					break;
				}
			}
		}
		catch (int e)
		{
			t.setAll( ERROR, "", line );
		}

		checkError(t.getK());
		
		out << t.output() << endl;
		if (t.getK() == ERROR)
		{
			return;
		}

	}
	out << "Total Tokens = " << amt;
}

bool Scanner::space(char& c, int& line)
{
	if(isspace(c))
	{
		if (c == '\n' || c == '\r')
		{
			line++;
		}
		return true;
	}
	return false;
}

void Scanner::checkError (Kind k)
{
	if (k != ERROR)
			amt++;
}

string Scanner::scanString(ifstream &in)
{
	string ret = "";
	char c;
	bool error = false;

	while (in.get(c))
	{
		if (c == '\'')
		{
			if ( error)
			{
				throw 2;
			}
			return ret;
		}
		else if (c == '\n')
		{
			throw 7;
		}
		ret += c;
	}
	throw 3;
}



// Schemes, Facts, Rules, Queries, Id
Kind Scanner::scanIdent( char c, ifstream &in, string &token )
{
	short count = 1;
	bool upper = false;
	token += c;
	Kind ret = ID;

	if (!isalpha(c))
	{
		throw 1;
	}
	else if ( isupper(c) )
	{
		upper = true;
	}

	while (in.peek() && ret == ID)
	{
		if (isspace(in.peek()))
		{
			break;
		}
		else if (!isalnum(in.peek()))
		{
			break;
		}	
		else if (in.peek() == ':')
		{
			break;
		}
		in >> c;
		token += c;
		count++;
		checkI(ret,token,count,upper,in);
	}

	return ret;
}

void Scanner::checkI( Kind& ret, string& token, short &count, bool &upper, ifstream &in)
{
	if(upper && (!isalnum(in.peek()) || in.eof()) )
	{
		if (count == 5)
		{
			checkFR(ret,token);
		}
		else if (count == 7)
		{
			checkSQ(ret, token);
		}
	}
}

void Scanner::checkFR( Kind &ret, string &token)
{
	if (token == "Rules")
	{
		ret = RULES;
	}
	else if (token == "Facts")
	{
		ret = FACTS;
	}
}

void Scanner::checkSQ( Kind &ret, string &token )
{
	if (token == "Schemes")
	{
		ret = SCHEMES;
	}
	else if (token == "Queries")
	{
		ret = QUERIES;
	}
}
