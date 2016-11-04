#include "lab3.h"

using namespace std;
						//DONE?
string findDict(string word, set<string> &dict)
{
////FOR LOOP
    set<string>::const_iterator iterator = dict.lower_bound(word) ;
    if( iterator == dict.end() ) 
    { /* no match */ 
    	return "" ; 
    }
    else if( *iterator == word ) 
    { /* exact match */ 
    	return *iterator ; 
    }
    else
    {
        /* check for prefix match */
        const string& candidate = *iterator ;
        if( candidate.size() > word.size() && candidate.substr( 0, word.size() ) == word )
        { /* found closest match */ 
        	return candidate ; 
        }
        else 
        { /* no match */ 
        	return "" ; 
        }
    }
    return "";
}

// find the row from the vector index		//DONE
int findRow(unsigned int q)
{
	if(q == 0)
		return 1;
	else if(q == 1)
		return 1;
	else if(q == 2)
		return 1;
	else if(q == 5)
		return -1;
	else if(q == 6)
		return -1;
	else if(q == 7)
		return -1;
	else
		return 0;
}

// find the column from the vector index		//DONE
int findCol(unsigned int q)
{
	if(q == 0)
		return -1;
	else if(q == 2)
		return 1;
	else if(q == 3)
		return -1;
	else if(q == 4)
		return 1;
	else if(q == 5)
		return -1;
	else if(q == 7)
		return 1;
	else
		return 0;
}

// return NULL if out of bounds		//DONE
string isNull(vector<vector<string>> &board, int i, int j)
{
	if((i < 0) || (i > (board.size()-1)) || (j < 0) || (j > (board.size()-1)))
		return ".";
	else
		return board[i][j];
}

//Create fake board		//DONE
vector<string> miniBoard(vector<vector<string>> &board, int i, int j)
{
	vector<string> v;
	v.push_back(isNull(board, i--, j--));
	v.push_back(isNull(board, i--, j));
	v.push_back(isNull(board, i--, j++));
	v.push_back(isNull(board, i++, j--));
	v.push_back(isNull(board, i, j--));
	v.push_back(isNull(board, i++, j++));
	v.push_back(isNull(board, i++, j));
	v.push_back(isNull(board, i, j++));
	return v;
}

//recursively search the board			// everything you need should be there
void searchBoard(vector<vector<string>> &board, set<string> &dict, unsigned int i, unsigned int j, set<string>& dout, string str = "")
{
	str += board[i][j];
	if((findDict(str, dict) == "") || i > board.size())
		return;
	else if(findDict(str, dict) == str)					// FINISH THIS
	{
		dout.insert(str);
		return;
	}
	vector<string> v = miniBoard(board, i, j);
	for(unsigned int q = 0; q < v.size(); q++)
	{
		if(v[q] == ".")
			continue;
		else
			searchBoard(board, dict, i+findRow(q), j+findCol(q), dout, str);//Recursion...should work
	}
	v.clear();
	return;
}

void boardSearch(vector<vector<string>> &board, set<string> &dict, set<string>& dout)
{
	for(unsigned int i = 0; i < board.size(); i++)
	{
		for(unsigned int j = 0; j < board.size(); j++)
		{
			searchBoard(board, dict, i, j, dout);
		}
	}

}

// Load the dictionary file		//DONE
void openDict(string arg, set<string> &dict)
{
	string str;
	ifstream in;
	in.open(arg);
	while(getline(in,str))
	{
		if(str.size() > 3)
		{
			transform(str.begin(), str.end(), str.begin(), ::tolower);	// lowercase
			dict.insert(str);
		}
	}
	in.close();
}


// load the board file		//DONE
void openBoard(string arg, vector<vector<string>> &board)			// works!!!
{
	string str;
	ifstream in;
	vector<string> v;
	in.open(arg);
	while(in >> str)
	{
		transform(str.begin(), str.end(), str.begin(), ::tolower);		// lowercase
		v.push_back(str);
	}
	in.close();
	int row_col = sqrt(v.size());
	for(int i = 0; i < row_col; i++ )
	{
		board.push_back(vector <string>());
		for(int j = 0; j < row_col; j++)
			board[i].push_back(v[((i*row_col)+j)]);
	}
}

int main(int argc, char* argv[])
{
	set<string> words;
	set<string> dict;
	vector<vector<string>> board;
	set<string> dout;
	openDict(argv[1], dict);			// open dictionary file
	openBoard(argv[2], board);			// open board file
	
	ofstream out;
	out.open(argv[3]);					// open output
	
	boardSearch(board, dict, dout);
	
	// out = to out.txt
	for(unsigned int i = 0; i < board.size(); i++)			// board output
	{
		for (unsigned int j = 0; j < board.size(); j++)
			out << board[i][j] << " ";
		out << endl;
	}
	out << endl;
	for(set<string>::iterator i = dout.begin(); i != dout.end(); i++) // iterate through set to output
	{
		out << *i << endl;
	}
//	out.close();
//	system("pause");
}
