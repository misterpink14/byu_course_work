/*
* @author Benjamin Thompson
* @title Project 1
* @class CS 236
*
*	TOKEN Header
*		Write a scanner that reads a sequence of characters from a text file, 
*		identifies the datalog language tokens found in the file, and outputs 
*		each token to an output file.
*/

#ifndef TOKEN_H_
#define TOKEN_H_

#include <string>
#include <sstream>

using std::stringstream;
using std::string;

enum Kind
{
	COMMA,			// 1
	PERIOD,			// 2
	Q_MARK,			// 3
	LEFT_PAREN,		// 4
	RIGHT_PAREN,	// 5
	COLON,			// 6
	COLON_DASH,		// 7
	SCHEMES,		// 8
	FACTS,			// 9
	RULES,			// 10
	QUERIES,		// 11
	ID,				// 12
	STRING,			// 13
	ERROR
};


class Token
{
	private:
		Kind k;
		string value;
		int line;
		
	public:
		Token();

		Token( Kind type, string v, int l );
	
		void setAll( Kind type, string v, int l );

		void setK( Kind type );
		
		Kind getK();
		
		void setValue( string v );
		
		string getValue();
		
		void setLine( int l );
		
		int getLine();
		
		string output();
};

#endif /* TOKEN_H_ */