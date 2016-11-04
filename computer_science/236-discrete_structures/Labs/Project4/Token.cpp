/*
* @author Benjamin Thompson
* @title Project 1
* @class CS 236
*
*    TOKEN
*		Write a scanner that reads a sequence of characters from a text file, 
*		identifies the datalog language tokens found in the file, and outputs 
*		each token to an output file.
*/

#include "Token.h"


Token::Token() {}
//Token::Token() : k(), value(""), line(-1) {}


Token::Token( Kind type, string v, int l ) : k(type), value(v), line(l) {}

void Token::setAll(Kind type, string v, int l)
{
	k = type;
	value = v;
	line = l;
}

void Token::setK( Kind type )
{
	k = type;
}
		
Kind Token::getK()
{
	return k;
}

void Token::setValue( string v )
{
	value = v;
}

string Token::getValue()
{
	if ( value != "" )
		return value;
	else
		return "";
}

void Token::setLine( int l )
{
	line = l;
}

int Token::getLine()
{
	return line;
}

string Token::output()
{
	stringstream out;
	out << "(";
	switch(k)
	{
		case COMMA:
			out << "COMMA";
			break;
		case PERIOD:
			out << "PERIOD";
			break;
		case Q_MARK:
			out << "Q_MARK";
			break;
		case LEFT_PAREN:
			out << "LEFT_PAREN";
			break;
		case RIGHT_PAREN:
			out << "RIGHT_PAREN";
			break;
		case COLON:
			out << "COLON";
			break;
		case COLON_DASH:
			out << "COLON_DASH";
			break;
		case SCHEMES:
			out << "SCHEMES";
			break;
		case FACTS:
			out << "FACTS";
			break;
		case RULES:
			out << "RULES";
			break;
		case QUERIES:
			out << "QUERIES";
			break;
		case ID:
			out << "ID";
			break;
		case STRING:
			out << "STRING";
			break;
		case ERROR:
			out.str(std::string());
			out << "Input Error on line " << line;
			return out.str();
	}
	out << ",\"" << value << "\"," << line << ")";
	return out.str();
}
