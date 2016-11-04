#include <iostream>
#include <string>

using namespace std;

int main()
{
	int degree;
	string temp;

	cin >> degree >> temp;

	if (temp == "F")
	{
		degree = (degree - 32)*(5);
		degree = degree / 9;
		temp = " C";
	}
	else
	{
		if(temp == "C")
		{
			degree = degree * 9;
			degree = degree / 5;
			degree = degree + 32;
			temp = " F";
		}
		
	}
	cout << endl << degree << temp << endl;
	system("pause");
	return 0;
}