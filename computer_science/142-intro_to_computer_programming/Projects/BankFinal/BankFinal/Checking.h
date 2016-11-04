#include "Account.h"

class Checking: public Account
{
	public:
		Checking(int acc, double bal, string user);

		/*
			advanceMonth()

			Regular Checking:

			A regular checking accounts has a monthly fee of 6 US dollars
			which is deducted  automatically from the balance
		*/
		virtual void advanceMonth();

		/*
			withdrawFromSavings(double amount)

			If called from any checking account, it must return false.
		*/

		bool withdrawFromSavings(double amount);

		/*
			writeCheck(amount)

			Regular Checking:
			If ( current balance - amount ) is below zero, apply a $5 penalty fee to the current balance and return 
			false. Otherwise subtract the amount from the current balance and return true.
		*/

		virtual bool writeCheck(double amount);

		virtual ~Checking(){}

};




class Checking1: public Checking
{
	public:
		Checking1(int acc, double bal, string user);	
		/*
			advanceMonth()

			Checking+:
			There is no monthly fee for Checking+ accounts unless a monthly fee is imposed.
			The monthly fee of 6 US dollars is imposed only if the current balance drops below 300 US dollars.
		*/
		void advanceMonth();

		/*
			writeCheck(amount)

			Checking+:
			If the ( current balance - amount) is at least 300 dollars, subtract the amount from the current balance and return true.
			If the ( current balance - amount) is below  300 dollars, impose a monthly fee of $6, subtract the amount from the current
			balance, and return true.  If there are insuffient funds, apply a $5 fee to the current balance and return
			false.
		*/

		virtual bool writeCheck(double amount);

		virtual ~Checking1(){}

};



class Checking2: public Checking
{
	public:
		Checking2(int acc, double bal, string user);


		/*
			advanceMonth()

			Checking++:
			There is no monthly fee for Checking++ accounts unless a monthly fee is imposed.
			The montly fee of 6 US dollars is imposed only if the current balance drops below 300 US dollars.
			Checking++ gains monthly interest of 1/12 of .5% (Checking ++ earns .5% per year; therefore
			earns .005/12 per month) only if the current balance is 800 or more. The monthly interest is 
			forfeited if the current balance drops below 800 US dollars.
		*/
		void advanceMonth();

		/*
			writeCheck(amount)

			Checking++:
			If the ( current balance - amount) is at least 800 dollars, substract the amount from the current balance
			and return true. If the current balance drops below 800, take away the monthly interest,
			subtract the amount from the current balance and return true. If it drops below $300, impose a monthly fee of $6. If there are insuffienct funds, immediately apply a $5 fee 
			to the current balance.

		*/

		virtual bool writeCheck(double amount) = 0;

		virtual ~Checking2(){}

};