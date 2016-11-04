/*
	This is my work(:
			Benjamin Thompson
			Section 2

TEST CASE 1
				Add the player John, then add to the line-up twice, fight
				Draw count added. WORKS!
TEST CASE 2
				Add the player John and Ben, then add both to the line-up, fight
				Random throw works, updated properly. WORKS!
TEST CASE 3
				Fight with only John in the line-up
				Error. WORKS!
*/

#include <iostream>
#include <vector>
#include <string>
#include "Player.h"
#include <cstdlib>
#include <time.h>

using namespace std;



/*
	Menu serves as the main menu for the program. It stores the user's selection so the main
	function can perform the appropriate function.
	@return option		the user's selected option
*/
int Menu()
{
	int option;
	while(1)
	{
		cout << "Select one of the following options: \n" <<
			"\t1 - Show Players\n" << 
			"\t2 - Add Player\n" <<
			"\t3 - Add To Line-Up\n" <<
			"\t4 - Show Line-Up\n" << 
			"\t5 - Fight\n" <<
			"\t0 - Quit\n";
		cin >> option;
		cin.sync();					// For invalid
		cin.clear();				// input
		if(option >= 0 && option <= 5)
			break;
		else
			cout << "Invalid input\n\n";
	}
	return option;
}




/*
	The Players function displayes all the player's names, wins, losses, and draws as stored
	in the AllPlayers array.
	@param AllPlayers	A vector of the Player class including a list of all the players in the game
*/
void Players(vector <Player*> &AllPlayers)
{
	for(int i = 0; i < AllPlayers.size(); i++)
	{
		cout << (*AllPlayers[i]).toString();
	}
}




/*
	The findName function finds a specific name in the given vector and returns the Player's location
	@param input		user's inputted name
	@param playerList	list of players
	@return				location of player, or an invalid location if player does not exist
*/
int findName(string input, vector <Player*> &playerList)
{
	for(int i = 0; i < playerList.size(); i++)
	{
		if((*playerList[i]).strName() == input)
			return i;
	}
	return (playerList.size() + 1);
}

	

/*
	The Add function add's a player to the AllPlayer array or the LineUp array as requested
	by the user.
	@param
*/
void Add(vector <Player*> &playerList)
{
	int playerLoc;					// location of the player being searched for

	while(1)
	{
		string input;
		cout << "What is the name of the player you wish to add?\n";
		getline(cin,input);
		playerLoc = findName(input, playerList);
		if (playerLoc < playerList.size()){
			cout << "This player already exists.\n\n";
		}
		else{
			playerList.push_back(new Player(input));
			break;
		}
	}
	
	return;
}




/*
	The AddLineUp function adds a player to the line-up after verifying that the user is inputted
	into the program.
	@param AllPlayers	shows the list of all the Players added by the user
	@param LineUp		shows the list of all the Players in the line-up added by the user
*/
void AddLineUp(vector <Player*> &AllPlayers, vector <Player*> &LineUp)
{
	string input;						// user's input
	int playerLoc;						// location of the Player looking for
	cout << "What is the name of the player you wish to add?\n";
	getline(cin,input);					// Allow for multiple word input

	playerLoc = findName(input, AllPlayers);	// store location of Player

	if(playerLoc < AllPlayers.size()){			// add to line up?
		LineUp.push_back(AllPlayers[playerLoc]);
	}
	else{
		cout << "This player does not exist\n\n";
	}
	return;
}




/*
	The LineUp function displays the names of all the players in the line-up as stored in the
	LineUp array
	@param LineUp	the list of all the Players added to the line-up
*/
void ShowLineUp(vector <Player*> &LineUp)
{
	for(int i = 0; i < LineUp.size(); i++)
	{
		cout << (*LineUp[i]).strName() << "\n\n";
	}
}




/*
	The Fight function begins a game of Rock Paper Sissors with the top two opponents in the
	line-up.
	@param LineUp	the list of all the Players added to the line-up
*/
void Fight(vector <Player*> &LineUp)
{
	const int FIRST = 0;				// the first name in the line-up
	const int SECOND = 1;				// the second name in the line-up
	
	const int MIN = 2;					// the minimum players to fight

	string player1Throw;				// store the first Player's throw
	string player2Throw;				// store the second Player's throw
	string rock = "Rock";				// rock beats sissors
	string paper = "Paper";				// paper beats rock
	string sissors = "Sissors";			// sissors beats paper
	
	if(LineUp.size() < MIN){			// not enough players?
		cout << "There are not enough players in the line-up.\n\n";
		return;
	}
										// same Player?
	else if(LineUp[FIRST] == LineUp[SECOND]){
		cout << (*LineUp[FIRST]).strName() << " is listed as the first and second player in the line up.\n"
			<< "By default, the match ends in a draw.\n\n";
		(*LineUp[FIRST]).addDraw();
	}
	else{
		// get each Player's throw
		player1Throw = (*LineUp[FIRST]).getRPSThrow();
		player2Throw = (*LineUp[SECOND]).getRPSThrow();
		
		// output
		cout << (*LineUp[FIRST]).strName() << " vs. " << (*LineUp[SECOND]).strName() <<
			"\n\n" << (*LineUp[FIRST]).strName() << " throws " << player1Throw << "\n" << 
			(*LineUp[SECOND]).strName() << " throws " << player2Throw << "\n\n";

		// the game
		if(player1Throw == rock){
			if(player2Throw == rock){
				cout << "It's a DRAW!\n\n";
				(*LineUp[FIRST]).addDraw();
				(*LineUp[SECOND]).addDraw();
			}
			else if(player2Throw == paper){
				cout << (*LineUp[SECOND]).strName() << " WINS!\n\n";
				(*LineUp[FIRST]).addLoss();
				(*LineUp[SECOND]).addWin();
			}
			else if(player2Throw == sissors){
				cout << (*LineUp[FIRST]).strName() << " WINS!\n\n";
				(*LineUp[FIRST]).addWin();
				(*LineUp[SECOND]).addLoss();
			}
		}
		else if(player1Throw == paper){
			if(player2Throw == rock){
				cout << (*LineUp[FIRST]).strName() << " WINS!\n\n";
				(*LineUp[FIRST]).addWin();
				(*LineUp[SECOND]).addLoss();
			}
			else if(player2Throw == paper){
				cout << "It's a DRAW!\n\n";
				(*LineUp[FIRST]).addDraw();
				(*LineUp[SECOND]).addDraw();
			}
			else if(player2Throw == sissors){
				cout << (*LineUp[SECOND]).strName() << " WINS!\n\n";
				(*LineUp[FIRST]).addLoss();
				(*LineUp[SECOND]).addWin();
			}
		}
		else{
			if(player2Throw == rock){
				cout << (*LineUp[SECOND]).strName() << " WINS!\n\n";
				(*LineUp[FIRST]).addLoss();
				(*LineUp[SECOND]).addWin();
			}
			else if(player2Throw == paper){
				cout << (*LineUp[FIRST]).strName() << " WINS!\n\n";
				(*LineUp[FIRST]).addWin();
				(*LineUp[SECOND]).addLoss();
			}
			else if(player2Throw == sissors){
				cout << "It's a DRAW!\n\n";
				(*LineUp[FIRST]).addDraw();
				(*LineUp[SECOND]).addDraw();
			}
		}
	}

	for(int i = 2; i < LineUp.size(); i++)
	{
		LineUp[i-2] = LineUp[i];
	}
	LineUp.pop_back();
	LineUp.pop_back();

	return;
}




/*
	The main function of the program.
*/
int main()
{
	vector <Player*> AllPlayers;		// stores all players
	vector <Player*> LineUp;			// stores the line-up for the game

	// options from the menu 
	const int ONE = 1;					// option one from the menu
	const int TWO = 2;					// option two from the menu
	const int THREE = 3;				// option three from the menu
	const int FOUR = 4;					// option four from the menu
	const int FIVE = 5;					// option five from the menu

	srand (time(NULL));					// set random seed

	int option;							// user input selected from the menu function

	do
	{
		option = Menu();				// to store user selected option

		// the functions for each menu option
		if(option == ONE)
		{
			Players(AllPlayers);
			cout << endl;
		}
		else if(option == TWO)
		{
			Add(AllPlayers);
		}
		else if(option == THREE)
		{
			AddLineUp(AllPlayers, LineUp);
		}
		else if(option == FOUR)
		{
			ShowLineUp(LineUp);
			cout << endl;
		}
		else if(option == FIVE)
		{
			Fight(LineUp);
		}
	}
	while(option != 0);				// repeat unless quit
	system("pause");
	return 0;
}