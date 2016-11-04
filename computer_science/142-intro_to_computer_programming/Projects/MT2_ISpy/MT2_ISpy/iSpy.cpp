/*************************************************************************************************
	NAME:	Benjamin Thompson
	SID:	03-432-2827
	CS 142 Fall 2013 Midterm 2
**************************************************************************************************
	TEST CASES:
	Test 1: 
		Select >> option 1 // Input >> On top of a hill // Input >> 3
		Output << Rq#wrs#ri#d#kloo
		CORRECT
	Test 2:
		Select >> option 3 // Input >> Rq#wrs#ri#d#kloo
		output << On top of a hill
		CORRECT
	Test 3:
		Select >> option 5 // Input >> Rq#wrs#ri#d#kloo // Input >> 6 // Input >> 3,3,3,3,3,3
		Output << On top of a hill
		CORRECT
**************************************************************************************************/

#include <iostream>
#include <vector> 
#include <string>

using namespace std;


/*************************************************************************************************
	menu is the menu for the program. The user selects an option and that value is saved in a 
	memory location
	@return option	the memory location of the user's input;
*************************************************************************************************/
int menu()
{
	int option;
	bool fail = true;
	do
	{
		cout << "--------------------------------------------\n" 
			<< "Select one of the following choices: \n"
			<< "0 - Quit\n" <<
			"1 - Encrypt text using the Ceasar Cipher and a key\n" <<
			"2 - Decrypt text using the Ceasar Cipher and a key\n" <<
			"3 - Decrypt text using the Ceasar Cipher without the key\n" <<
			"4 - Encrypt text using the \"Super Cipher\" and a key\n" <<
			"5 - Decrypt text using the \"Super Cipher\" and a key\n" <<
			"6 - Decrypt text using the \"Super Cipher\" without the key\n";
		cin >> option;
		cin.sync();
		cin.clear();
		if(option <= 6 && option >= 0)
			fail = false;
		else
			cout << "Invalid input. Please try again \n\n";
	
	}
	while(fail == true);
	return option;
}


/*******************************************************************************************
	The output function creates a string by converting numerical values, that represent 
	specific characters, stored in a vector.
	@param characters	vector containing numerical representations of characters
	@return output		string of characters converted from the characters vector
*******************************************************************************************/
string output(vector<int> & characters)
{
	string str = "";				// empty string to store converted characters
	int encode;						// int to store values to be converted to a character

	// convert numbers in characters to string str
	for (int letter = 0; letter < characters.size(); letter++)
	{
		encode = characters[letter];
		str += (char) encode;
	}
	return str; 
}


/******************************************************************************
	The outNum function displays the numerical representation of a string
	@param text		The text to be displayed numerically
******************************************************************************/
void outNum(string text)
{
	int out;			// to store value to be outputed as a specific character

	// output numbers to converted string
	for(int i = 0; i < text.size(); i++)
	{
		out = text[i];
		cout << out << " ";
	}
	cout << endl;
}


/**************************************************************************************
	The endecrypt function encrypts or decrypts a message as requested by the user
	for the Ceasar Cipher.
	@param characters	vector containing numerical representations of characters
	@param text			text to be encrypted or decrypted
	@param option		user selected option
	@param key			user defined key for decryption/encryption
**************************************************************************************/
void endecrypt(vector<int> & characters, string text, int option, int key)
{
	int valChar;					// decimal character value
	const int MAX = 122;			// maximum value for character conversion
	int wrapAround = 91;			// to wrap around the character values
	const int MIN = 32;				// minimum calue for character conversion
	const int enCC = 1;				// option one from the menu
	const int deCC = 2;				// option two from the menu

	// encrypt/decrypt
	for(int letter = 0; letter < text.size(); letter++)
	{
		valChar = text[letter];
		if(option == enCC)
		{
			valChar += key;
			if(valChar > MAX)
			{
				valChar -= wrapAround;
			}
		}
		else if(option == deCC)
		{
			valChar -= key;
			if(valChar < MIN)
			{
				valChar += wrapAround;
			}
		}
		characters.push_back(valChar);
	}
	
}



/**************************************************************************************
	The resetVector function deletes all the values of the vector.
	@param characters	the vector containing decimal representations of a string
**************************************************************************************/
void resetVector(vector<int> & characters)
{
	int resetValue = characters.size();					// loop iterations to reset the value

	// clear the vector
	for(int i = 0; i < resetValue; i++)
	{
		characters.pop_back();
	}
}



/*********************************************************************************************
	The findDuplicates function finds duplicates being tested for in the findKey function
	@param check			the value currently being tested
	@param noDuplicates		stores the values already tested
**********************************************/
bool findDuplicates(int check, vector<int>& noDuplicates)
{
	bool dup = false;
	for(int i = 0; i < noDuplicates.size(); i++)
	{
		if(check == noDuplicates[i])
			dup = true;
	}
	return dup;
}

/****************************************************************************************
	The findKey function is used to find the key to decrypt the message in option 3.
	@param characters	the vector containing decimal representations of a string
	@param text			the text inputed by the user
****************************************************************************************/
int findKey(vector<int> & characters, string text)
{
	int option = 2;					// used for decryption
	int key = 0;					// to display values before decryption
	int check;						// to check for the most used character
	int most = 0;					// to hold the most used character
	int most2;						// to hold the second most used character
	int amt1;						// amount of iterations of a character
	int amt2;						// amount of iterations of a character
	int amtm = 0;					// amount of iterations of the most used character
	const int TOP2 = 2;				// to find the top two used characters
	const int MAX = 122;			// maximum character value accepted
	const int MIN = 32;				// minimum possible value for character conversion
	const int FIRSTRUN = 1;			// first iteration of the first for loop
	vector <int> noDuplicates;		// to remove duplicates from testing in the loop

	// store the current numerical values of the user's text
	endecrypt(characters, text, option, key);
	
	// find the two most used values
	for(int p = 0; p < TOP2; p++)
	{
		amt2 = 0;
		for(int j = 0; j < characters.size(); j++)
		{
			check = text[j];
			amt1 = 0;
			if(findDuplicates(check, noDuplicates) == false)
			{
				if(check < MIN)
					check += 91;
				if(check > MAX)
					check -= 91;
				for(int i = 0; i < characters.size(); i++)
				{
					if(check == text[i] && text[i] != most)
					{
						amt1++;
					}
				}
				noDuplicates.push_back(check);
				if (p < FIRSTRUN) // output all tested characters and their usage amount
				{
					cout << "\"" << (char) check << "\"" << " which is the ASCII " 
						<< check << " occurs " << amt1 << " time(s)\n";
				}
				if(amt1 > amt2)
				{
					amt2 = amt1;
					most2 = check;
				}
			}
		}
		if(amt2 > amtm)
		{
			amtm = amt2;
			most = most2;
		}
		resetVector(noDuplicates);
	}
	
	// output 2 most used characters
	cout << "\n\"" << (char) most << "\"" << " which is the ASCII " 
				<< most << " occurs " << amtm << " time(s)\n";
	cout << "\"" << (char) most2 << "\"" << " which is the ASCII " 
				<< most2 << " occurs " << amt2 << " time(s)\n";
	// find key
	resetVector(characters);
	key = most - MIN;
	bool yes = false;
	do
	{
		string input;				// used to verify decryption
		endecrypt(characters, text, option, key);
		cout << "\nDoes the following message match the origional(Y/N)? \n";
		cout << output(characters) << endl;
		cin >> input;
		if(input == "Y" || input == "y")
		{
			yes = true;
		}
		else if(input == "N" || input == "n")
		{
			key = most2 - 32;		// use the second most used character
			resetVector(characters);
		}
		else
		{
			cout << "\nInvalid ipnut. Please try again. \n";
		}
	}
	while(yes == false);
	return key;
}



/********************************************************************************************
	The CeaserCipher function uses the Caesar Cipher to encrypt/decrypt the user's input
	@param option	the user selected option from the menu
********************************************************************************************/
void CeaserCipher(int option)
{
	string text;							// user inputted message
	string decrypted = "decrypted";			// for output
	string encrypted = "encrypted";			// for output
	const int enCC = 1;						// option one from menu
	const int deCC = 2;						// option 2 from menu
	const int dewokCC = 3;					// option 3 from menu
	int key;								// key for decryption/encryption
	vector<int> characters;					// decimal value of each character in the variable text

	// have the user input text to be encrpyed/decrypted
	if(option == enCC)
		cout << "Please enter the text to encrypt: ";
	else if(option == deCC || option == dewokCC)
		cout << "Please enter the encrypted text: ";
	getline(cin, text);

	// have the user enter the key to use for encryption/decryption	
	if(option == enCC)
		cout << "\nPlease enter the key to use for encryption:";
	else if(option == deCC)
		cout << "\nPlease enter the key to use for decryption:";
	if(option != dewokCC)
		cin >> key;

	// output numerical values of text
	cout << "\nConverted to a vector<int>: ";
	outNum(text);

	if(option == dewokCC)	// call the findKey function to crack the key
		key = findKey(characters, text);
	
	// decrypt/encrypt (option 1/2)
	if(option == enCC || option == deCC)
	{
		endecrypt(characters, text, option, key);
	}

	// output new message to the user
	text = output(characters);	
	cout << "\nConverted ints: ";
	outNum(text);
	cout << "\nHere is your ";
	if(option == enCC)
		cout << encrypted;
	else
		cout << decrypted;
	cout << " message: ";
	
	cout << text << "\n\n";
	return;
}



/**************************************************************************************
	The endecryptSC function encrypts or decrypts a message as requested by the user
	for the "Super Cipher".
	@param characters	vector containing numerical representations of characters
	@param text			text to be encrypted or decrypted
	@param option		user selected option
	@param key			user defined keys for decryption/encryption
**************************************************************************************/
void endecryptSC(vector<int> & characters, string text, int option, vector<int> & key, int keys)
{
	int valChar;					// decimal character value
	const int MAX = 122;			// maximum value for character conversion
	const int wrapAround = 91;			// to wrap around the character values
	const int MIN = 32;				// minimum calue for character conversion
	const int enSC = 4;				// option 4 from the menu
	const int deSC = 5;				// option 5 from the menu

	// encrypt/decrypt
	int x = 0;
	for(int j = 0; j < text.size(); j += keys)
	{
		for(int letter = 0; letter < keys && x < (text.size()); letter++)
		{
			valChar = text[(letter + j)];
			if(option == enSC)
			{
				valChar += key[letter];
				if(valChar > MAX)
				{
					valChar -= wrapAround;
				}
				x++;
			}
			else if(option == deSC)
			{
				valChar -= key[letter];
				if(valChar < MIN)
				{
					valChar += wrapAround;
				}
				x++;
			}
			characters.push_back(valChar);
		}
	}
}


void findKeySC(vector <int> & characters, string text, int keys)
{
	int option = 2;							// for calling the endecrypt function
	int currentValue = 0;					// for calling the endecrypt function
	int amt, amt1, amt2, check, most = 0;	// values to find the most used character
	vector<int> key;						// keys to encrypt/decrypt
	vector<int> noDuplicates;				// to check for duplicates

	// store the current numerical values of the user's text
	endecrypt(characters, text, option, currentValue);
	
	// find the most used values
	for(int i = 0; i < keys; i++)
	{
		
		amt2 = 0;
		for(int j = i; j < characters.size(); j += keys)
		{
			check = text[j];
			amt1 = 0;
			amt = 0;
			for(int p = i; p < characters.size(); p += keys)
			{
				if(check == text[p])
				{
					if(text[p] != most)
						amt1++;
					amt++;
				}
			}
			if(amt1 > amt2)
			{
				amt2 = amt1;
				most = check;
			}
			
			cout << "\"" << (char) check << "\"" << " which is the ASCII " 
					<< check << " occurs " << amt << " time(s)\n";
		}
		key.push_back(most);
	}

	option = 5;					// to set the vector characters to the proper value
	resetVector(characters);
	endecryptSC(characters, text, option, key, keys);
}


/*****************************************************************************************
	The SuperCipher function uses a super cipher to encrypt/decrypt the users message
	@param option	the user selected option from the menu
*****************************************************************************************/
void SuperCipher(int option)
{
	string text;							// user inputted message
	string decrypted = "decrypted";			// for output
	string encrypted = "encrypted";			// for output
	const int enSC = 4;						// option 4 from menu
	const int deSC = 5;						// option 5 from menu
	const int dewokSC = 6;					// option 6 from menu
	vector<int> characters;					// decimal value of each character in the variable text
	int keys;

	// have the user input text to be encrpyed/decrypted
	if(option == enSC)
		cout << "Please enter the text to encrypt: ";
	else if(option == deSC || option == dewokSC)
		cout << "Please enter the encrypted text: ";
	getline(cin, text);
	cout << "How many keys would you like to use?: ";
	cin >> keys;

	vector<int> key(keys);						// keys for decryption/encryption

	// have the user enter the key to use for encryption/decryption	
	if(option == enSC)
		cout << "\nPlease enter the " << keys
			<< "  keys to use for encryption:";
	else if(option == deSC)
		cout << "\nPlease enter the four keys to use for decryption:";
	if(option != dewokSC)
	{
		for(int i = 0; i < keys; i++)
			cin >> key[i];
	}
	
	cout << "\nConverted to a vector<int>: ";
	outNum(text);								// output numerical value of text

	if(option == dewokSC)		// call the findKeySC function to crack the keys
		findKeySC(characters, text, keys);

	// decrypt/encrypt (option 1/2)
	if(option == enSC || option == deSC)
	{
		endecryptSC(characters, text, option, key, keys);
	}
	
	// output new message to the user
	text = output(characters);
	cout << "\nConverted ints: ";
	outNum(text);							// output numerical value of new text
	cout << "\nHere is your ";
	if(option == enSC)
		cout << encrypted;
	else
		cout << decrypted;
	cout << " message: " << output(characters) << endl;
	return;
}


/*****************************************
	The main function of the program
*****************************************/
int main()
{
	int option;											// user selected option

	// available options for the user from the menu
	const int enCC = 1, deCC = 2, dewokCC = 3;			// encrypt/decrypt/decrypt w/o key // Caesar Cipher
	const int enSC = 4, deSC = 5, dewokSC = 6, QUIT = 0;// encrypt/decrypt/decrypt w/o key // Super Cipher
	
	do		// main loop for the program
	{
		option = menu();
		
		// Ceaser Cipher options
		if(option == enCC || option == deCC || option == dewokCC)
			CeaserCipher(option);
		// Super Cipher options
		else if(option == enSC || option == deSC || option == dewokSC)
			SuperCipher(option);
	}
	while(option != QUIT);				// quit only if requested

	system("pause");
	return 0;
}