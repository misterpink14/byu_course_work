#include "Player.h"

using namespace std;

Player::Player(string newName)
{
	name = newName;
	wins = 0;
	losses = 0;
	draws = 0;
}

string Player::getRPSThrow()
{
	int ran = rand() % 3 + 1;
	if(ran == 1){
		return "Rock";
	}
	else if(ran == 2){
		return "Paper";
	}
	else{
		return "Sissors";
	}
}

double Player::winRecord()
{
	if((wins + losses + draws) == 0)
		return 0;
	double record;
	record = (double) wins / ((double) wins + (double) losses + (double) draws);
	return record;
}

string Player::toString()
{
	stringstream toString;
	toString <<	"Name: " << name
		<< "\n\tWins: " << wins
		<< "\n\tLosses: " << losses
		<< "\n\tDraws: " << draws 
		<< "\n\tWin Record: " << winRecord() << endl;
	return toString.str();
}

string Player::strName()
{
	return name;
}

void Player::addDraw()
{
	draws++;
	return;
}

void Player::addLoss()
{
	losses++;
	return;
}

void Player::addWin()
{
	wins++;
	return;
}