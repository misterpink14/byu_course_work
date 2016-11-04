#include <string>
#include <fstream>
#include <vector>
#include <iostream>
#include <algorithm>
#include <sstream>
#include <iomanip>

using namespace std;



class Student
{
	public:
		Student(string n, string s, string p, string a)
		{
			name = n;
			stId = s;
			phone = p;
			address = a;
		}
		string showName() {return name;}
		
		string showId() {return stId;}

		string showPhone() {return phone;}

		string showAdd() {return address;}

		bool operator < (Student s) const {
    	return stId < s.stId ;
  	}

	private:
		string name;
		string stId;
		string phone;
		string address;
};


