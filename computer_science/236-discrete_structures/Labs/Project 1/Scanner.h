/*
* @author Benjamin Thompson
* @title Project 1
* @class CS 236
*
*    SCANNER Header
*		Write a scanner that reads a sequence of characters from a text file, 
*		identifies the datalog language tokens found in the file, and outputs 
*		each token to an output file.
*/

#include "Token.h"
#include <cctype>
#include <iostream>
#include <fstream>
#include <queue>
#include <vector>

using std::ifstream;
using std::ofstream;
using std::cout;
using std::endl;
using std::queue;

class Scanner
{
	private:
		//queue<Token> tList;
		int amt;
		
	public:
		Scanner();
		
		void scan( ifstream &in, ofstream &out );
		
		bool space(char& c, int& line);
		
		void checkError (Kind k);

		string scanString(ifstream &in);

		Kind scanIdent( char c, ifstream &in, string &token );
		
		void checkI( Kind& ret, string& token, short &count, bool &upper, ifstream& in);

		void checkFR(Kind &ret, string &token);

		void checkSQ(Kind &ret, string &token);
	
};
