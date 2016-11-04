#include "Parser.h"


/*

*/
void Parser::Parse(vector<Token> &tList)
{
	try
	{
		DatalogProgram Prog;
		vector<Token>::iterator it = tList.begin();
		// Schemes -> Identifier(PARAMLIST)

		// Facts -> Identifier(PARAMLIST).

		// Rules -> Identifier(PARAMLIST) :- PREDICATELIST

		// Queries -> Identifier(PARAMLIST) ?


	}
	catch (Token e)
	{

	}
}