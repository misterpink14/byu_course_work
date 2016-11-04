#include "lab2.h"

using namespace std;


void checkLine(string &input)
{
	for (unsigned int i = 0; i < input.size(); i++) 
	{
		if(!isalpha(input[i])) 
			input[i] = ' ';
	}
}

// populate dict set
void makeDict(set<string> &dict, string arg)
{
	ifstream file;
	string input;	

	file.open(arg);						// open 1st input file
	while (getline(file,input)){
		stringstream input1;
		checkLine(input);
		transform(input.begin(), input.end(), input.begin(), ::tolower);
		//lowerCase(input);			// tolower(input)
		input1 << input;
		while(input1 >> input)
		{
			dict.insert(input);		// input each word to dict set
		}
	}
	file.close();
}



void checkDoc(set<string> &dict, map<string, list<int>> &misspell, string arg)
{
	ifstream file;
	int line = 1;
	string word;

	file.open(arg);					// open 1st input file
	while (getline(file,word))
	{
		stringstream input;
		checkLine(word);
		input << word;
		// dictCheck(input, word, dict);
		
		while(input >> word)
		{
			transform(word.begin(), word.end(), word.begin(), ::tolower);
			if(dict.count(word) == 0)
			{
				misspell[word].push_back(line);
			}
		}
		line++;
	}
}

//main
int main(int argc, char* argv[])
{
	set<string> dict;										// fill set requirement
	map<string, list<int>> misspell;	// hold mispelled words and row #
	//stringstream spellch;									// run spell check on

	makeDict(dict, argv[1]);	// accept dict file

	checkDoc(dict, misspell, argv[2]);	// accept doc

	ofstream out;
	out.open(argv[3]);
//	set<string>::iterator i;
//	for(i = dict.begin(); i != dict.end(); i++)
//		cout << *i << endl;


	for(map<string,list<int>>::const_iterator Walker = misspell.begin(); Walker != misspell.end(); ++Walker)
	{
		out << Walker->first << ": ";
		
		for (list<int>::const_iterator iterator = Walker->second.begin(); iterator != Walker->second.end(); ++iterator) {
    	out << *iterator << ' ';
}
//		for(set<int>::const_iterator WalkerVector = Walker->second.begin(); WalkerVector != Walker->second.end(); ++WalkerVector)
	//		{
		//		out << *WalkerVector << " ";
			//}
		out << endl;
	}
	
	
	out.close();
	return 0;
}
