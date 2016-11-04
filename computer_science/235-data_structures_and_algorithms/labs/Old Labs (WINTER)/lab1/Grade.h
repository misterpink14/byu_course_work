#include "Student.h"

class Grade
{
	public:
		Grade(string id, string grd, string cl)
		{
			stId = id;
			grade = grd;
			classId = cl;
		}
		
		string showId() { return stId;}

		string showGrade() { return grade;}

		string showClassId() { return classId;}
		
		bool operator < (Grade g) const {
	    return stId < g.stId ||
  	    (stId == g.stId && classId < g.classId) ||
  	    (stId == g.stId && classId == g.classId && grade < g.grade);
		}

	private:
		string stId;
		string grade;
		string classId;
		
};
