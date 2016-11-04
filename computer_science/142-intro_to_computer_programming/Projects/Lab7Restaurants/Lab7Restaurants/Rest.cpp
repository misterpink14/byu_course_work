/**
TEST 1
Display Restaurants
All are properly displayed

TEST 2
Display, Add RED and Display
WORKS
Display, Delete RED, and Display
WORKS

TEST 3
RUN the tournament.
WORKS when picking Wendy's and In-N-Out
*/


#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <time.h>
#include <math.h>

using namespace std;

/**********************************************************
	menu contains the menu of the program.
	@return input	Return's the user selected option.
***********************************************************/

string menu()
{
	bool verify = false;										// To verify the user's input is valid
	string input;												// store user input
	const int SIZE = 6;											// the number of options in the menu
	string option [SIZE] = {"1","2","3","4","T","Q"};
	while (verify == false)
	{
		cout << "SELECT ONE OF THE FOLLOWING:\n" << 
			"Type 1 to display the restaurants in their current order\n" <<
			"Type 2 to add a restaurant\n" << 
			"Type 3 to remove a restaurant\n" <<
			"Type 4 to shuffle the list of restaurants\n" <<
			"Type T to begin the tournament\n" <<
			"Type Q to QUIT\n";
		cin >> input;
		for(int i = 0;i < SIZE; i++)
		{
		if(input == option[i]){
			verify = true;
			cout << endl;
		}
		}
		if(verify == false){
			cout << "\nInvalid selection\n\n";
		}
	}
	return input;
}



/*******************************************************************************************
	initRest is responsible for storing 16 restaraunts into the addressed vector(rest).
	@param rest		the address of the vector that needs to be initialized
*******************************************************************************************/

void initRest(vector<string> & rest)
{
	rest.push_back("Wendy's");
	rest.push_back("FiveGuys");
	rest.push_back("RedLobster");
	rest.push_back("Applebee's");
	rest.push_back("Chili's");
	rest.push_back("TGIFriday");
	rest.push_back("Denny's");
	rest.push_back("TacoBell");
	rest.push_back("Tucanos");
	rest.push_back("BrickOven");
	rest.push_back("Malawi'sPizza");
	rest.push_back("HappySumo");
	rest.push_back("CafeRio");
	rest.push_back("JDawgs");
	rest.push_back("SLABPizza");
	rest.push_back("In-N-Out");
}



/*******************************************************************
	dispRest displays the Restaurants stored in the vector rest
*******************************************************************/
void dispRest(vector<string> & rest)
{
	for(int i = 0; i < rest.size(); i++)
		{
		cout << rest[i];
		if(i < (rest.size() - 1))
			cout << ", ";
		else
			cout << "\n\n";
		}
}



/*************************************************************************************************************
	inRest has 2 purposes. If requested by the addRest function, then the return value indicates that
	the user input is already in the list of Restaurants. If requested by the removeRest function, inRest
	will set the last value of the vector rest to the location of the Restaurant requested to be removed.
	@param rest		the vector hlding a list of Restaurants
	@param test		the Restaurant being tested for (input from user)
	@param request	the option that is requesting the information
	@return name	if the restaurant is in the list = true
*************************************************************************************************************/

bool inRest(vector<string> & rest, string test, int request)
{
	int remove = 2;										// Indicates option two is calling the function
	bool name = false;									// By default function assumes the user's input is not in the vector
	for(int i = 0; i < rest.size(); i++)
	{
		if(rest[i] == test){
			name = true;
			if(request == remove)
			{
				rest[i] = rest[rest.size()-1];
			}
		}
	}
	return name;
}




/***************************************************************
	addRest adds a new restaurant to the current list
	@param rest		Vector containing a list of Restaurants
***************************************************************/
void addRest(vector<string> & rest)
{
	string input;
	const int REQUEST = 1;								// For calling the inRest function
	bool inVector;										// Returned from inRest function // used to add restaurant
	cout << "What is the name of the restaurant you wish to add(exclude spaces)?\n";
	cin >> input;
	inVector = inRest(rest, input, REQUEST);
	if(inVector == false)
	{
		rest.push_back(input);
		cout << "This Restaurant has been added to the line-up.\n\n";
	}
	else
	{
		cout << "This Restaurant is already in the line-up.\n\n";
	}
}



/***************************************************************
	removeRest removed a restaurant that the user inputted
	@param rest		Vector containing a list of Restaurants
****************************************************************/
void removeRest(vector<string> & rest)
{
	string input;												// to store user's input
	const int REQUEST = 2;										// for calling inRest function
	bool inVector;												// used to indicate that the Restaurant was removed
	cout << "What is the name of the restaurant you wish to remove(exclude spaces)?\n";
	cin >> input;
	inVector = inRest(rest, input, REQUEST);
	if(inVector == true)
	{
		rest.pop_back();
		cout << "This Restaurant has been removed from the line-up.\n\n";
	}
	else
	{
		cout << "This Restaurant is not in the line-up.\n\n";
	}
}




/*****************************************************************
	shuffle shuffles the Restaurants stored in the vector rest
	@param rest		Vector containing a list of Restaurants
*****************************************************************/
void shuffle(vector<string> & rest)
{
	string one, two;								// To store the restaurants to be swapped
	int random1, random2;							// random values
	for(int i = 0; i < rest.size(); i++)
	{
		random1 = rand() % rest.size() + 1;
		random2 = rand() % rest.size() + 1;
		random1 -= 1;
		random2 -= 1;
		one = rest[random1];
		two = rest[random2];
		rest[random1] = two;
		rest[random2] = one;
	}
}



/**************************************************************
	okay checks to see if it is okay to run the tournament
**************************************************************/
bool okay(vector<string> & rest)
{
	bool ok = false;								// default: not okay to run the tournament
	int exponent = 1;								// value for n of 2^n
	double vsize = rest.size();						// hold size of vector
	int twos = 2;									// hold powers of 2
	const int TWO = 2;								// to raise powers of 2
	while(vsize >= twos)
	{
		exponent++;
		if(vsize == twos)
		{
			ok = true;
			return ok;
		}
		else
		{
			for(int j = 1; j < exponent; j++)
			{
				twos = twos * TWO;
			}
		}
	}
	return ok;
}



/*********************************************************************************************************
	fight begins the tournament. The user chooses their favorite Restaurant, between two Restaurants,
	until there is only one left
	@param restaurants	a copy of the rest vector
	@param				the number of rounds
*********************************************************************************************************/
void fight (vector<string> & rest, int round)
{
	const int ONE = 1;								// Option one for battle
	const int TWO = 2;								// Option to for battle
	int vone = 0;									// First option for battle
	int vtwo = (rest.size() - 1);					// Second option for battle
	int input;										// So the user can select their favorite Restaurant
	int bound = rest.size() / 2;					// Bounds for each Round
	int roundFinder = rest.size() / 2;				// To find the total rounds
	int counter;									// To keep the iterations of each Round within the bounds
	int match;										// Hold the match number
	int totalRound = 1;								// Holds the total Rounds for the tournament
	while(roundFinder > 1)
	{
		totalRound++;
		roundFinder = roundFinder / 2;
	}
	do					// Rounds
	{
		counter = 0;
		vone = 0;
		match = 1;	
		do				// Match per round
		{
			
			bool works = true;
			do			// Verify the users input is valid
			{
				cout << "Match: " << match << "/" << bound << "\tRound: " << round << "/" << totalRound 
					<< "\nChoose your favorite: \n" << "1-" << rest[vone] << "\n\tVS\n" 
					<< "2-" << rest[vtwo] << "\n\n";
				cin >> input;
				if(input == ONE)
				{
					rest.pop_back();
				}
				else if(input == TWO)
				{
					
					rest[vone] = rest[vtwo];
					rest.pop_back();
				}
				else
				{
					cout << "\nINVALID INPUT. Try again\n\n";
					works = false;
				}
			}
			while(works == false);
			counter++;
			vone++;
			match++;
			vtwo = (rest.size() - 1);
		}
		while(counter < bound);
		bound = rest.size() / 2;
		round++;
	}
	while((rest.size()) > 1);
	cout << "\n" << rest[0] << " is the winner!!!\n\n";
}



/****************************************************************************************************
	The main function. Responsible for running the nessicary functions at the appropriate time
*****************************************************************************************************/
int main ()
{
	vector<string> rest;							// For holding the names of restaurants
	initRest(rest);									// To store restaurant names
	string option;									// User's selected option
	int round = 1;									// round number
	
	srand (time(0));								// Initialize random seed
	do
	{
		option = menu();							// Store the user's selection from the menu
		if(option == "1")
		{
			dispRest(rest);
		}
		else if(option == "2")
		{
			addRest(rest);
		}
		else if(option == "3")
		{
			removeRest(rest);
		}
		else if(option == "4")
		{
			shuffle(rest);
		}
		else if(option == "T")
		{
			if(okay(rest) == true)					// Verify the restaurant count is acceptable
			{
				fight(rest, round);
				round++;
			}
			else
			{
				cout << "\nERROR\n" <<
					"The size of the Restaurant list must be a power of 2 (2^n)\n\n";
			}
		}
	}
	while(option != "Q");
	system("pause");
	return 0;
}