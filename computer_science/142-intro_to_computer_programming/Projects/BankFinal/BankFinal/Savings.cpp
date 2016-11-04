#include "Savings.h"





Savings::Savings(int acc, double bal, string user) : Account(acc, bal, user){}

void Savings :: advanceMonth()
{
	balance = balance + (balance * (.01/12));
}

void Savings:: deposit(double amount)
{
	balance += amount;
}

bool Savings:: withdrawFromSavings(double amount)
{
	if((balance - amount) > 0){
		balance -= amount;
		return true;
	}
	else{
		balance -= FEES;
		return false;
	}
}

bool Savings:: writeCheck(double amount){return false;}

Savings:: ~Savings(){}


//--------------------------------------------------

Savings1::Savings1(int acc, double bal, string user) : Savings(acc, bal, user){}

void Savings1 :: advanceMonth()
{
	balance = balance + (balance * (.0125/12));
}

bool Savings1 :: withdrawFromSavings(double amount)
{
	if((balance - amount) < 1000){
		balance = balance + (balance * (.01/12));
	}
	else{
		balance = balance + (balance * (.0125/12));
	}
}

Savings1 :: ~Savings1(){}


//-------------------------------------
CD::CD(int acc, double bal, string user) : Savings(acc, bal, user){}

void CD :: advanceMonth()
{
	month++;
	balance = balance + (balance * (.02/12));
}

bool CD :: withdrawFromSavings(double amount)
{
	if(month < 9)
		balance = balance + (balance * (.02/12));
	if((balance - amount) < 0){
		balance -= FEES;
		return false;
	}
	else{
		balance -= amount;
		return true;
	}
}

CD :: ~CD(){}