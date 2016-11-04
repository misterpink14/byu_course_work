#include "Account.h"






class Savings: public Account
{
	public:
		Savings(int acc, double bal, string user);
		/*
			advanceMonth()

			Regular Savings:
			Regular Savings has no monthly fee and earns interest of 1% per year. (Regular Savings earns
			.01/12 of interest per month)
		*/

		virtual void advanceMonth();

		/*
			deposit(double amount)

			All accounts allow deposits. The amount of the deposit is added to the current balance.
		*/

		virtual void deposit(double amount);

		/*
			withdrawFromSavings(double amount)
			
			Regular Savings:
			Withdraw only if the balance remains nonnegative. If it drops below 0 when attempting to withdraw, 
			a fee of 5 US dollars is imposed immediately on the account; return false. 
			Return true otherwise and deduct the amount from the currentBalance.
		*/

		bool withdrawFromSavings(double amount);

		/*
			writeCheck(amount)

			If called from any saving/CD account, return false.
			
		*/

		bool writeCheck(double amount);

		virtual ~Savings(){}

};




class Savings1: public Savings
{
	public:
		Savings1(int acc, double bal, string user);

		/*
			advanceMonth()

			Savings+:
			Earns interest of 1.25% per year. If the balance drops below 1000 US dollars, the interest drops to 1% per year. 
		*/

		virtual void advanceMonth();

		/*
			withdrawFromSavings(double amount)

			Savings+:
			Return true if the (current - amount) is at least 1000 US dollars. Return true, but drop interest
			from .125% to .1% if the balance drops below 1000 dollars. Return false if the (current balance - amount) drops below 0 and
			apply a $5 fee to the current balance. 
		*/

		bool withdrawFromSavings(double amount);

		virtual ~Savings1(){}

};



class CD: public Savings
{
	public:
		CD(int acc, double bal, string user);

		/*
			advanceMonth()

			CD:
			CD's earn interest of 2% per year. If part or all of the CD account is withdrawn from before maturity (9 months), then
			any interest since the withdrawal date is forfeited.
		*/

		virtual void advanceMonth();

		/*
			withdrawFromSavings(double amount)

			CD:
			Return false if a withdrawal occurs before maturity (9 months), deduct the amount from the current balance, and forfeit
			any interest since the withdrawl date. Return true otherwise and withdraw all of the current balance. If insuffient funds,
			apply a $5 fee to the current balance.
		*/

		bool withdrawFromSavings(double amount);

		virtual ~CD(){}

};