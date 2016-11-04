#include <iostream>
#include <string>

using namespace std;

int main()
{
	string byu = "BYU";
	string space = ", ";
	string output;
	int input;
	int x = 0;

	cin >> input;

	while (x < input)
	{
		output += byu;
		cout << endl << output;
		output += space;
		x++;
	}

	cout << endl;

	system("pause");
	return 0;
}