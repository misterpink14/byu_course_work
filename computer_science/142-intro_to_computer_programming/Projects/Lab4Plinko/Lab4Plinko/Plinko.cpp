/*
Test 1
Expected
Input:		1	-1
Output:		Return to menu
Actual
Output		$1000
Fixed Issue.

Test 2
Input:		2	2	2
Output:		$$$$$
Actual
Output		$0	$0

Test 3
Input:		1	8
Output:		$$$
Actual
Output		$500
*/

#include <iostream>
#include <string>
#include <cstdlib>
using namespace std;

int main()
{
	string menuIn;
	double input;
	string one = "1";
	string multi = "2";
	string quit = "Q";
	int win = -50;

	do
	{
		int avgWin;
		int totalWin = 0;
		int chips = 1;
		bool chipDropped = true;
		cout << "Select one of the following: \n" <<
			"Drop one chip into one slot (type 1)\n" <<
			"Drop multiple chips into one slot (type 2)\n" <<
			"Quit the program (Type Q)\n";
		cin >> menuIn;
		if (menuIn == one || menuIn == multi)
		{
			cout << "\nSelect a slot from 0-8: ";
			cin >> input;
			cout << endl;
			if (input < 0 || input > 8)
				chipDropped = false;
			if (menuIn == multi && chipDropped == true)
				{
						cout << "Select the number of chips you wish to drop:  ";
						cin >> chips;
				}
			if (chips < 1)
				chipDropped = false;
			if (chipDropped == true)
			{
				for(int i = 0; i < chips; i++)
				{
					double slot = input;
					if (menuIn == one)
						cout << slot << " ";
					for(int j = 0; j < 12; j++)
					{
						int x;
						x = rand() % 2;
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
				}
			}
			if (menuIn == one && chipDropped == true)
			{
				cout << "\n\nYou are awarded $" << totalWin << "\n\n";
			}
			else if (menuIn == multi && chipDropped == true)
			{
				avgWin = totalWin / chips;
				cout << "\nYou are awarded $" << totalWin << 
					"\nYour average earnings are $" << avgWin << "\n\n";
			}
		}
	}
	while(menuIn != quit);
	system("pause");
	return 0;
}