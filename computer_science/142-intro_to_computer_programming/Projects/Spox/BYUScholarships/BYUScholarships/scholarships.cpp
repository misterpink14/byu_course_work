#include <iostream>
#include <string>

using namespace std;

int main()
{
	double GPA;
	int credits;
	string award;

	cin >> GPA >> credits >> award;

	if (award == "Yes")
		cout << "Please apply again next year";
	else
	{
		if ((GPA >= 2.93 & credits >= 14)|(GPA >= 3.9))
		{
			if (GPA >= 3.5)
				cout << "\nCongratulations! You have been awarded: $8000\n";
			else
				cout << "\nCongratulations! You have been awarded: $5000\n";
		}
		else
			cout << "Please apply again next year";
	}
	system("pause");
	return 0;
}