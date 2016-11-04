#include <iostream>

using namespace std;

    int main()
    {
        double pi = 3.14159;
        double radius, height, volume;
        
        cin >> radius >> height;
        
        volume = pi * radius * radius * height;
        cout << volume << endl;
        system("pause");
        return 0;
    }