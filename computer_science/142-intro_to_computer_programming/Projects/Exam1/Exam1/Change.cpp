/*
Test 1				Menu Option:	U.S. Dollars
INPUT				1				85
					Burton		Seppi		Clement		Child		Tee-A
EXPECTED OUTPUT		1			1			1			1			1
ACTUAL OUTPUT		SAME

________________________________________________________________________________
Test 2				Menu Option:	U.S. Dollars
INPUT				2				85
					Burton		Seppi		Clement		Child		Tee-A
EXPECTED OUTPUT		0			0			0			1			2
					0			0			0			1			1
					0			0			0			1			0
					0			0			0			0			2
					0			0			0			0			1
ACTUAL OUTPUT		SAME

________________________________________________________________________________
Test 3				Menu Option:	U.S. Dollars
INPUT				2				85
					Burton		Seppi		Clement		Child		Tee-A
EXPECTED OUTPUT		0			0			0			1			2
					0			0			0			1			1
					0			0			0			1			0
					0			0			0			0			2
					0			0			0			0			1
ACTUAL OUTPUT		SAME

*/

#include <iostream>
#include <string>

using namespace std;

/*
	The menu function serves as the program's menu. The function asks the user to make a selection,
	then returns the value of that selection to the main function. There are no parameters.
	@return input	The user's selection from the given menu.
*/
int menu()
{
	int input;										// used to store the users selection from the menu
	cout << "Select one of the following (1-4)\n"
		<< "1. Exchange U.S. dollars to C-MASMAS coins\n"
		<< "2. Show a list of equivalents\n"
		<< "3. Exit the program\n"
		<< "4. Exchange U.S. dollars to C-MASMAS coins, mainly in your preffered coin\n\n";
	cin >> input;
	cout << endl;
	return input;									// return the user's selection to main()
}
/*
	The exchange function is used to exchange U.S. dollars to C-MASMAS coins. 44 dollars is equal to
	one Burton. 29 dollars is equal to one Seppi. 8 dollars is equal to one Clement. 3 dollars is
	equal to one Child. 1 dollar is equal to one Tee-A. This function returns nothing and has two
	parameters.
	@param USdollars	The amount of money that the user inputted.
	@parap menu_select	The option the user selected from the main menu.
*/
void exchange(int USdollars, int menu_select)
{
	int counter;									// the limit of the counter in the for loop
	int dollars;									// used to decrement the 
	const int MENU_ONE = 1;							// the constant associated with selection 1 from the menu
	const int MENU_TWO = 2;							// the constant associated with selection 2 from the menu
	if(menu_select == MENU_ONE){					// for loop runs once if for selection 1 from menu
		counter = 1;
	}
	else if (menu_select == MENU_TWO){				// for loop runs the as many times as the user inputted
		cout << "List:\n";							// dollar amount indicates if 2 is selected from menu
		counter = USdollars;
	}
	for(int x = 0; x < counter; x++){				// displays and calculates the exchange rate to C-MASMAS
		int burton = 0;								// to store the amount of Burton coins, default 0
		const int BURTON_VALUE = 44;				// the exchange rate for Burton coins
		int seppi = 0;								// to store the amount of Seppi coins, default 0
		const int SEPPI_VALUE = 29;					// the exchange rate for Seppi coins
		int clement = 0;							// to store the amount of Clement coins, default 0
		const int CLEMENT_VALUE = 8;				// the exchange rate for Clement coins
		int child = 0;								// to store the amount of Child coins, default 0
		const int CHILD_VALUE = 3;					// the exchange rate for Child coins
		int tee_a = 0;								// to store the amount of Tee-A coins, default 0
		const int TEE_A_VALUE = 1;					// the exchange rate for Tee-A coins
		dollars = USdollars;						// used in the for loop to evaluate the coins

		cout << "Here is your change for $" << dollars << "\n\n";

		while(dollars >= BURTON_VALUE){				// finds the amount of Burton coins
			burton++;
			dollars -= BURTON_VALUE;
		}
		cout << "Burton:\t\t" << burton << endl;

		while(dollars >= SEPPI_VALUE){				// finds the amount of Seppi coins
			seppi++;
			dollars -= SEPPI_VALUE;
		}
		cout << "Seppi:\t\t" << seppi << endl;

		while(dollars >= CLEMENT_VALUE){			// finds the amount of Clement coins
			clement++;
			dollars -= CLEMENT_VALUE;
		}
		cout << "Clement:\t" << clement << endl;

		while(dollars >= CHILD_VALUE){				// finds the amount of Child coins
			child++;
			dollars -= CHILD_VALUE;
		}
		cout << "Child:\t\t" << child << endl;

		while(dollars >= TEE_A_VALUE){				// finds the amount of Tee-A coins
			tee_a++;
			dollars -= TEE_A_VALUE;
		}
		cout << "Tee-a:\t\t" << tee_a << "\n\n";

		USdollars--;								// decrements U.S. dollars (for menu option 2)
	}
	
}
/*
	The prefered_exchange function is similar to the exchange function, but applied to option number.
	The program provides the exchange rate of U.S. dollars to C-MASMAS coins, mainly in the user 
	prefered coin. There is no return value.
	@param USdollars	The amount of money. in U.S. dollars the user wishes to have exchanged.
*/
void prefered_exchange (int USdollars)
{
	string prefered_coin;							// used to store the user's prefered coin

	int burton = 0;									// to store the amount of Burton coins, default 0
	const int BURTON_VALUE = 44;					// the exchange rate for Burton coins
	int seppi = 0;									// to store the amount of Seppi coins, default 0
	const int SEPPI_VALUE = 29;						// the exchange rate for Seppi coins
	int clement = 0;								// to store the amount of Clement coins, default 0
	const int CLEMENT_VALUE = 8;					// the exchange rate for Clement coins
	int child = 0;									// to store the amount of Child coins, default 0
	const int CHILD_VALUE = 3;						// the exchange rate for Child coins
	int tee_a = 0;									// to store the amount of Tee-A coins, default 0
	const int TEE_A_VALUE = 1;						// the exchange rate for Tee-A coins
	int dollars = USdollars;						// used to evaluate the coins

	cout << "What is your prefered coin?\n";
	cin >> prefered_coin;

	// the following evaluates and displays the exchange to the user
	if(prefered_coin == "Burton" || prefered_coin == "burton"){
		if(dollars < BURTON_VALUE){
			cout << "\nERROR. The coin value is larger than the value of U.S. dollars.\n\n";
			return;
		}
		while(dollars >= BURTON_VALUE){
			burton++;
			dollars -= BURTON_VALUE;
		}
	}
	else if(prefered_coin == "Seppi" || prefered_coin == "seppi"){
		if(dollars < SEPPI_VALUE){
			cout << "\nERROR. The coin value is larger than the value of U.S. dollars.\n\n";
			return;
		}
		while(dollars >= SEPPI_VALUE){
			seppi++;
			dollars -= SEPPI_VALUE;
		}
	}
	else if(prefered_coin == "Clement" || prefered_coin == "clement"){
		if(dollars < CLEMENT_VALUE){
			cout << "\nERROR. The coin value is larger than the value of U.S. dollars.\n\n";
			return;
		}
		while(dollars >= CLEMENT_VALUE){
			clement++;
			dollars -= CLEMENT_VALUE;
		}
	}
	else if(prefered_coin == "Child" || prefered_coin == "child"){
		if(dollars < CHILD_VALUE){
			cout << "\nERROR. The coin value is larger than the value of U.S. dollars.\n\n";
			return;
		}
		while(dollars >= CHILD_VALUE){
			child++;
			dollars -= CHILD_VALUE;
		}
	}
	else if(prefered_coin == "Tee-A" || prefered_coin == "Tee-a" 
		|| prefered_coin == "tee-a" || prefered_coin == "tee-A"){
		if(dollars < TEE_A_VALUE){
			cout << "\nERROR. The coin value is larger than the value of U.S. dollars.\n\n";
			return;
		}
		while(dollars >= TEE_A_VALUE){
			tee_a++;
			dollars -= TEE_A_VALUE;
		}
	}
	else {											// if the user input is invalid
		cout << "/nINVALID COIN NAME\n\n";
		return;
	}

	cout << "Here is your change for $" << USdollars << "\n\n";
	while(dollars >= BURTON_VALUE){
		burton++;
		dollars -= BURTON_VALUE;
	}
	cout << "Burton:\t\t" << burton << endl;
	while(dollars >= SEPPI_VALUE){
		seppi++;
		dollars -= SEPPI_VALUE;
	}
	cout << "Seppi:\t\t" << seppi << endl;
	while(dollars >= CLEMENT_VALUE){
		clement++;
		dollars -= CLEMENT_VALUE;
	}
	cout << "Clement:\t" << clement << endl;
	while(dollars >= CHILD_VALUE){
		child++;
		dollars -= CHILD_VALUE;
	}
	cout << "Child:\t\t" << child << endl;
	while(dollars >= TEE_A_VALUE){
		tee_a++;
		dollars -= TEE_A_VALUE;
	}
	cout << "Tee-a:\t\t" << tee_a << "\n\n";
}

/*
	The main function for the program
*/
int main()
{
	int menu_select = 0;								// Stores the user's selection from the menu
	const int SELECT_ONE = 1;							// The constant associated with option 1 from the menu
	const int SELECT_TWO = 2;							// The constant associated with option 2 from the menu
	const int SELECT_FOUR = 4;							// The constant associated with option 4 from the menu
	int USdollars;										// Stores the amount of U.S. dollars for exchange

	do
	{
		menu_select = menu();							// call the menu
		if(menu_select == SELECT_ONE || menu_select == SELECT_FOUR){
			cout << "How many U.S. dollars do you wish to exchange? Must be greater than 0\n";
			cin >> USdollars;
			if (USdollars > 0){
				if (menu_select == SELECT_FOUR){
					prefered_exchange(USdollars);		// call the function for option 4
				}
				else
					exchange(USdollars, menu_select);	// call the function for options 1 and 2
			}
		}
		else if(menu_select == SELECT_TWO){
			cout << "How many U.S. dollars do you wish to begin your list with? Must be greater than 0\n";
			cin >> USdollars;
			if (USdollars > 0){
				exchange(USdollars, menu_select);		// call the function for options 1 and 2
			}
		}
	}
	while(menu_select != 3);
	system("pause");
	return 0;
}