#include <iostream>

using namespace std;

int main()
{
	int input;
	int x = 0;

	cin >> input;

	while (x < input)
	{
		x++;
		cout << endl << x;
	}
	if (x == input)
	{
		cout << "\nREADY OR NOT, HERE I COME!\n";
	}

	system("pause");
	return 0;
}