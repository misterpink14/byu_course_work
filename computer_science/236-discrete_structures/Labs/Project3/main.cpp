/*
* @author Benjamin Thompson
* @title Project 1
* @class CS 236
*
*	DATALOG SCANNER
*		Write a scanner that reads a sequence of characters from a text file, 
*		identifies the datalog language tokens found in the file, and outputs 
*		each token to an output file.
*/

#include "DatalogProgram.h"
#include "Database.h"



/*
*	The main function for the program to run
*/
int main( int argc, const char* argv[] )
{
	// argv[1] input file
	// argv[2] output file

	ifstream in(argv[1]);
	ofstream out(argv[2]);

	DatalogProgram d;
	d.Parse(in, out);

	Database data;
	data.evaluate(out, d);

	in.close();
	out.close();

	system("pause");

}
