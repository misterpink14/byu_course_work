#include "Account.h"


Account :: Account(int acc, double bal, string user)
{
	month = 0;
	balance = bal;
	account = acc;
	name = user;
}

int Account :: getAccountNumber()
{
	return account;
}

double getCurrentBalance()
{
	return balance;
}

string Account :: getAccountOwner()
{
	return name;
}

void Account :: deposit(double amount)
{
	balance += amount;
}