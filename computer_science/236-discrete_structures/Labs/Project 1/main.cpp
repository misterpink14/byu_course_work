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

#include "Scanner.h"


/*
	Sends the output string to a given output text file.
*/


/*
*	The main function for the program to run
*/
int main( int argc, const char* argv[] )
{
	// argv[1] input file
	// argv[2] output file

	Scanner s;
	ifstream in(argv[1]);
	ofstream out(argv[2]);

	s.scan( in,out );

	
	in.close();
	out.close();

}
