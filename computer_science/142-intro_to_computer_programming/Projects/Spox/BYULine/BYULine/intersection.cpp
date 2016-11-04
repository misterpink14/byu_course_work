#include <iostream>
#include <string>

using namespace std;

int main()
{
	double x1, x2, x3, y1, y2, y3;
	double m1, m2, b1, b2;
	string t = "true";
	string f = "false";
	cin >> x1 >> y1 >> x2 >> y2 >> x3 >> y3;

	m1 = (y1 - y2) / (x1 - x2);
	m2 = (y2 - y3) / (x2 - x3);

	if (y3 > y1 & y2 > y3 & x3 > x1 & x2 > x3)
	{
		if (m1 == m2)
		{
			b1 = y1 - (m1 * x1);
			b2 = y3 - (m2 * x3);
			if (b1 == b2)
			{
				cout << endl << t << endl;
			}
			else if (x1 == x2 & x2 == x3)
				cout << endl << t << endl;
			else if (y1 == y2 & y2 == y3)
				cout << endl << t << endl;
			else
				cout << endl << f << endl;
		}
		else
		{
			if (x1 == x2 & x2 == x3)
				cout << endl << t << endl;
			else if (y1 == y2 & y2 == y3)
				cout << endl << t << endl;
			else
				cout << endl << f << endl;
		}
	}
	else
		cout << endl << f << endl;
	system("pause");
	return 0;

}