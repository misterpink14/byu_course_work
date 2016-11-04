#include <iostream>

using namespace std;

int main()
{
	int Total_Students;
	int Students_Per_Class = 30;
	int Amt_Of_Classes;
	int Remainder;

	cin >> Total_Students;
	
	Amt_Of_Classes = Total_Students / Students_Per_Class;
	Remainder = Total_Students % Students_Per_Class;

	cout << "Classrooms: " << Amt_Of_Classes
		<< " Remainder: " << Remainder << endl;

	system("pause");
	return 0;
}