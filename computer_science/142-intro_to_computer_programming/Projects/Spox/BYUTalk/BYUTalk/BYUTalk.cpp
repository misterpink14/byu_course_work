#include<iostream>
#include<string>

using namespace std;

int main()
{
    string input;
	cin >> input;
	if (input == "Hello")
		cout << "\nGlad to meet you\n";
	else
	{
		if (input == "Goodbye")
			cout << "\nSee you later\n";
	}
	system("pause");
	return 0;
}