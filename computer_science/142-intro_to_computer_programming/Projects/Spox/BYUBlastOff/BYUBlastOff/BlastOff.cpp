#include <iostream>

using namespace std;

int main()
{
	int input;

	cin >> input;
	cout<< endl << input << endl;
	int x = input;
	while (x > 0)
	{
		x--;
		cout << x << endl;
	}
	system("pause");
	return 0;
}