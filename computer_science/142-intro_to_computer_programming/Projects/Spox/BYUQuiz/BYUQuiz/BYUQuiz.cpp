#include <iostream>
#include <string>

using namespace std;

int main()
{
	string a, b;
	cin >> a >> b;
	if (a == "A")
	{
		if (b == "D")
			cout << "\nCredit\n";
		else
			cout << "\nNo credit\n";
	}
	else
	{
			if (a == "D")
		{
			if (b == "A")
				cout << "\nCredit\n";
			else
				cout << "\nNo credit\n";
		}
			else
				cout << "\nNo credit\n";
	}
	system("pause");
	return 0;
}