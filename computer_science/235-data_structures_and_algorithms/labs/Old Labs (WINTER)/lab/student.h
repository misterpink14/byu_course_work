//	Data Structures
#include <vector>
#include <list>
#include <set>
#include <string>

#include <algorithm>

#include <iostream>
#include <sstream>
#include <fstream>
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
		//		static int compCount = 0; 
	}

	Student()
		:name(""), stId(""), phone(""), address(""){}

	string showName() { return name; }

	string showId() { return stId; }

	string showPhone() { return phone; }

	string showAdd() { return address; }

	void resetCount() { compCount = 0; }

	int count() { return compCount; }

	bool operator < (Student s) const {
		compCount++;
		return stId < s.stId;
	}

	bool operator > (Student s) const {
		compCount++;
		return stId > s.stId;
	}

	bool operator == (Student s) const{
		compCount++;
		return stId == s.stId;
	}

 ~Student(){}
		
private:
	string name;
	string stId;
	string phone;
	string address;
	static int compCount;
}	myStudent;



int Student::compCount;