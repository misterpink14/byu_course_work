#include <iostream>
#include <string>
#include <iomanip>

using namespace std;
    int main()
    {
        string input;
        cin >> input;
        cout << fixed << input.substr(0,3)
            << endl;
        system("pause");
        return 0;
    }