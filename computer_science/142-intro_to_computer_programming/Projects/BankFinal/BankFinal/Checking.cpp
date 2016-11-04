#include "Checking.h"



Checking :: Checking(int acc, double bal, string user) : Account(acc, bal, user){}

void Checking :: advanceMonth()
{
	balance -= FEE;
}

bool Checking :: withdrawFromSavings(double amount)
{
	return false;
}

bool Checking :: writeCheck(double amount)
{
	if((balance - amount) < 0){
		balance -= 5;
		return false;
	}
	else{
		balance -= amount;
		return true;
	}
}

Checking :: ~Checking(){}

//---------------------------------------------

Checking1 :: Checking1(int acc, double bal, string user) : Checking(acc, bal, user){}

void Checking1 :: advanceMonth()
{
	if(balance < 300){
		balance -= FEE;
	}
}

bool Checking1 :: writeCheck(double amount)
{
	if((balance - amount) < 0){
		balance -= FEES;
		return false;
	}
	else if((balance - amount) >= 300){
		balance -= amount;
	}
	else{
		balance -= FEE;
	}
	return true;
}

Checking1 :: ~Checking1(){}

//---------------------------------------------

Checking2 :: Checking2(int acc, double bal, string user) : Checking(acc, bal, user){}

void Checking2 :: advanceMonth()
{
	if(balance < 300){
		balance -= FEE;
	}
	else if(balance >= 800){
		balance = balance + (balance * (.5/12));
	}
}

bool Checking2 :: writeCheck(double amount)
{
	if ((balance - amount) >= 800){
		balance -= amount;
	}
	else if((balance - amount) < 0){
		balance -= FEES;
		return false;
	}
	return true;
}


Checking2 :: ~Checking2(){}