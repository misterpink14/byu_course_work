#include <iostream>
#include <string>

using namespace std;

int main()
{
	int i;
	cin >> i;
	int p = i;
	string b = "BYU";
	int x = 0;
	while(x < i)
	{
		x++;
		for(int j = 0; j < x; j++)
		{
		cout << b;
		if (j < (x-1)){
			cout << ", ";
		}
		}
		cout << endl;
		p--;
	}
	system("pause");
	return 0;
}