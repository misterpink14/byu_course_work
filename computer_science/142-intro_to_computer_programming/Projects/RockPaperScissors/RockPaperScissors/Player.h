#include <string>
#include <cstdlib>
#include <sstream>

using namespace std;



class Player
{
private:
	string name;		// fighter's name
	int wins;			// fighter's wins
	int losses;			// fighter's losses
	int draws;			// fighter's draws

public:
	/*
		Constructor for a new instance of the class
		@param newName		the new name for the new object
	*/
	Player(string newName);
	
	
	/*
		@return rock, paper, or sissors (randomly selects)
	*/
	string getRPSThrow();
	
	
	/*
		@return the win record of the Player
	*/
	double winRecord();
	
	
	/*
		@return the name, wins, losses, draws, and win record as a string
	*/
	string toString();


	/*
		@return the name of the Player
	*/
	string strName();

	/*
		Add one to the Player's draws
	*/
	void addDraw();

	/*
		Add one to the Player's wins
	*/
	void addWin();

	/*
		Add one to the Player's losses
	*/
	void addLoss();
};