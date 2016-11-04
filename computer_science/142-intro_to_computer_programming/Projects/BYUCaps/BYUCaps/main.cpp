#include <iostream>
#include <string>
#include <cctype>
using namespace std;

int main()
{
    string lowerCase;
    
    getline(cin, lowerCase);
    
	for( int i = 0; i < lowerCase.length();i++){
		lowerCase[i] = toupper(lowerCase[i]);
   
	}
    cout << lowerCase << endl;
    system("pause");
    return 0;
}