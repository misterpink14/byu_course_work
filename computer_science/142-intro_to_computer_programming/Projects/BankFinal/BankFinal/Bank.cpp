#include "Bank.h"

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
		bool openAnAccount(string info)
		{
			int i = 0;
			int accNum;
			if((sizeof(acc)) < 1)
				accNum = 1;

			string account = "";
			for(i = 0; info[i] != ' '; i++){
				account += info[i];
			}

			string input = "";
			double balance;
			for(; info[i] != ' '; i++){
				input += info[i];
			}
			balance = std::stoi(info);
			if (balance <= 0)
				return false;
			
			string user = "";
			for(; info[i] != ' '; i++){
				user += info[i];
			}
			if (account == "Checking"){
				Checking act(accNum, balance, input);
			}
			else if(account == "Checking+"){
				Checking1 act(accNum, balance, input);
			}
			else if(account == "Checking++"){
				Checking2 act(accNum, balance, input);
			}
			else if(account == "Saving"){
				Savings act(accNum, balance, input);
			}
			else if(account == "Saving+"){
				Savings1 act(accNum, balance, input);
			}
			else if(account == "CD"){
				CD act(accNum, balance, input);
			}
			else return false;
			(acc).push_back(act);
			accNum++;
			return true;
		}

		/*
		   closeAnAccount(int accountNumber)

			Return true if the account is found, the current balance is positive, and the account removed from the Bank.
			Return false if the account is not found, or if the current balance is nonpositive. 
		*/
		bool closeAnAccount(int accountNumber)
		{
			for(int i = 0; i < sizeof(acc); i++)
			{
				if((acc[i].getAccountNumber())==accountNumber){
					if(acc[i].getBalance() < 0)
						continue;
					acc[i] = acc[sizeof(acc)-1];
					(acc).pop_back();
					break;
				}
			}
		}

		/*
			AccountInterface* getAnAccount(int accountNumber)

			Return an AccountInterface* object with the corresponding
			account number. Return NULL if the object is not found.

		*/

		AccountInterface* getAnAccount(int accountNumber)
		{
			for(int i = 0; i < sizeof(acc); i++)
			{
				if((acc[i].getAccountNumber())==accountNumber){
					return &acc[i];
				}
			}
			return NULL;
		}

		/*
			advanceMonth()

			Must advance month for all accounts.

		*/

		void advanceMonth()
		{
			for(int i = 0; i < sizeof(acc); i++){
				acc[i].advanceMonth();
			}
		}

		/*
			getNumberOfAccounts()

			Return the total amount of accounts in the Bank.
		*/;

		virtual int getNumberOfAccounts()
		{
			return sizeof(acc);
		}

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
