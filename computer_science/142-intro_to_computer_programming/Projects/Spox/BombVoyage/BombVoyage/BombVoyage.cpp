#include <iostream>
#include <string>

using namespace std;

int main()
{
	string input1, input2, input3;

	cin >> input1 >> input2 >> input3;

	if ( input1 == input2)
	{
		if (input2 == input3){
			cout << "\nDevice is armed. Do not open!\n";
		}
		else {
			cout << "\nThe device is not armed. You may proceed.\n";
		}
	}
	else
		cout << "\nThe device is not armed. You may proceed.\n";
	system("pause");
	return 0;
}