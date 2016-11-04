/**
Test 1
Expected
Input:		1	-1
Output:		Return to menu
Actual
Output		Correct

Test 2
Input:		2	2	2
Output:		$$$
Actual
Output		Correct

Test 3
Input:		1	8
Output:		$$$
Actual
Output		Correct
*/

#include <iostream>
#include <string>
#include <cstdlib>
using namespace std;

/**
	The main menu for Plinko
*/

string mainMenu()
{
	string menuIn;
	cout << "Select one of the following: \n" <<
			"Drop one chip into one slot (type 1)\n" <<
			"Drop multiple chips into one slot (type 2)\n" <<
			"Drop the same amount of chips into all 9 slots (type 3)\n" <<
			"Quit the program (Type Q)\n";
	cin >> menuIn;
	return menuIn;
}

/**
	Slot selection menu
*/

double slotSelect()
{
	double slot;
	cout << "\nSelect a slot from 0-8: ";
	cin >> slot;
	cout << endl;
	return slot;
}

/**
	Ask the user for the number of chips they wish to drop
*/

int numChips (string menuIn)
{
	const string all = "3";
	int chips;
	cout << "Enter the number of chips you wish to drop";
	if (menuIn == all)
		cout << " in each slot: ";
	else
		cout << ": ";
	cin >> chips;
	return chips;
}

/**
	Evaluate the total winnings for one chip
*/

int singleChip(string menuIn, double slot)
{
	const string one = "1";
	const string all = "3";
	int totalWin = 0;
	if (menuIn == one)
		cout << slot << " ";
	for(int j = 0; j < 12; j++){
		int x = rand() % 2;
		if (slot == 0)
			slot += 0.5;
		else if(slot == 8)
			slot -= 0.5;
		else if(x == 0)
			slot += 0.5;
		else if(x == 1)
			slot -= 0.5;
		if (menuIn == one)
			cout << slot << " ";
	}
	int win = -10000;
	if (slot == 0)
		win = 100;
	else if (slot == 1.0)
		win = 500;
	else if (slot == 2.0)
		win = 1000;
	else if (slot == 3.0)
		win = 0;
	else if (slot == 4.0)
		win = 10000;
	else if (slot == 5.0)
		win = 0;
	else if (slot == 6.0)
		win = 1000;
	else if (slot == 7.0)
		win = 500;
	else if (slot == 8.0)
		win = 100;
	totalWin += win;
	return totalWin;
}

/**
	Evaluate the total winnings for multiple chips (as requested by the user).
*/

int multiChip(string menuIn, double slot, int chips)
{
	int totalWin = 0;
	for(int i = 0; i < chips; i++){
		totalWin += singleChip(menuIn, slot);
	}
	return totalWin;
}

/**
	The main function.
*/
int main()
{
	string menuIn;
	string one = "1";
	string multi = "2";
	string all = "3";
	string quit = "Q";
	

	do
	{
		int avgWin;
		int totalWin = 0;
		int chips = 1;
		bool error = false;
		double slot = 0;

		menuIn = mainMenu();

		if (menuIn == quit){
			system("pause");
			return 0;
		}

		if (menuIn == one || menuIn == multi || menuIn == all){
			if (menuIn == one || menuIn == multi)
				slot = slotSelect();
			if (slot < 0 || slot > 8)
				error = true;
			if(menuIn== one && error == false){
				totalWin = singleChip(menuIn, slot);

				cout << "\n\nYou are awarded $" << totalWin << "\n\n";
			}
			else if (menuIn == multi && error == false){
				chips = numChips(menuIn);
				totalWin = multiChip(menuIn, slot, chips);

				if(chips != 0){
					avgWin = totalWin / chips;
					cout << "\nYou are awarded $" << totalWin << 
						"\nYour average earnings are $" << avgWin << "\n\n";
				}
				else
					avgWin = 0;
			}
			else if (menuIn == all && error == false){
				int totalSlots = 8;
				chips = numChips(menuIn);
				if (chips < 1)
					error = true;
				if (error == false){
					for(int x = 0; x <= totalSlots; x++){
						cout << "Slot number " << slot << endl;
						totalWin = multiChip(menuIn, slot, chips);
							
						avgWin = totalWin / chips;
						cout << "\nYou are awarded $" << totalWin << 
						"\nYour average earnings are $" << avgWin << "\n\n";
						slot++;
					}
				}
			}
		}
	}
	while(menuIn != quit);
	system("pause");
	return 0;
}