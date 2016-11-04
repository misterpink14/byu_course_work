#include "BankInterface.h"
#include "Account.h"
#include "Checking.h"
#include "Savings.h"

vector<AccountInterface> acc;

class Bank: public BankInterface
{
	public:
		Bank(){}

		/*
			openAnAccount(string info)

			Create a new account and add it to the Bank
			The information provided includes a type, a balance, and (a single first) name.
			Return true if the information is valid. 
			Return false if the balance is nonpositive ( 0 or less), if the type is not available, or
			if the opening balance amount for the type is insuffient.
			All accounts must be AccountInterface*, and must be added to a vector of AccountInterface*.



		*/

		virtual bool openAnAccount(string info);

		/*
		   closeAnAccount(int accountNumber)

			Return true if the account is found, the current balance is positive, and the account removed from the Bank.
			Return false if the account is not found, or if the current balance is nonpositive. 

		*/

		virtual bool closeAnAccount(int accountNumber);

		/*
			AccountInterface* getAnAccount(int accountNumber)

			Return an AccountInterface* object with the corresponding
			account number. Return NULL if the object is not found.

		*/

		virtual AccountInterface* getAnAccount(int accountNumber);

		/*
			advanceMonth()

			Must advance month for all accounts.

		*/

		virtual void advanceMonth();

		/*
			getNumberOfAccounts()

			Return the total amount of accounts in the Bank.
		*/

		virtual int getNumberOfAccounts();

		/*
		*****************************************************************************************
		Extra Credit - uncomment this section to add the extra credit function into your program
		*****************************************************************************************

		Implement “getOrderedAccounts(string criterion)” in the BankInterface. 
		The method must return a vector<AccountInterface*> sorted by a criterion. The criterion will 
		be a string that is “accountNumber”, “name”, or “balance”. You must sort the accounts by that 
		criterion. If the criterion is “accountNumber”, the vector must be sorted by increasing account 
		numbers ( 1,2,3…). If it is “name”, it must be sorted by increasing ASCII value ( A,B,C,a,b,c…).
		If the criteria is “balance”, the accounts must be sorted by nondecreasing balance value 
		( 100,230,1200,...).


		virtual vector<AccountInterface*> getSortedAccounts(string criteria) = 0;



		*/

		virtual ~Bank(){}		
};
