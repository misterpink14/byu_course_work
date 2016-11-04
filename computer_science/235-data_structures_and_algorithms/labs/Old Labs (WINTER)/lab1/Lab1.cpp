
#include "Grade.h"






vector<Student> firstOut(string arg)
{
	string s;
	ifstream in;					// for opening files
	vector<string> stlist;
	vector<Student> ret;


	in.open(arg);			// open 1st input file
	while (getline(in,s)){
		stlist.push_back(s);
	}
	if(stlist.size() == 0)
	{
		Student add("0","0","0","0");
		ret.push_back(add);
		return ret;
	}
	in.close();

  for(unsigned int i = 0; i < stlist.size(); i+=4)
	{
		Student add(stlist[(i+1)],stlist[i],stlist[(i+3)],stlist[i+2]);
		ret.push_back(add);
	}
	return ret;
}

vector<Grade> secondOut(string arg)
{
	vector<string> list;
	vector<Grade> grade;
	string s;
	ifstream in;

	in.open(arg);			// open 1st input file
	while (getline(in,s)){
		list.push_back(s);
	}
	
	in.close();

	for(unsigned int i = 0; i < list.size(); i+=3)
	{
		Grade st(list[(i+1)],list[(i+2)],list[i]);
		grade.push_back(st);
	}
	return grade;
}


void sortList(vector<Grade> &list)
{
	vector<Grade> st;
	vector<string> clList;
	
	for(unsigned int i = 0; i < list.size(); i++)
	{
		clList.push_back(list[i].showClassId());
	}

	sort(clList.begin(),clList.end());

	for(unsigned int i = 0; i < clList.size(); i++)
	{
		for(unsigned int j = 0; j < list.size(); j++)
		{
			if(list[j].showClassId() == clList[i])
			{
				st.push_back(list[j]);
				break;
			}
		}
	}
	
	list = st;
	
}

vector <string> thirdOut(string arg)
{
	vector <string> list;
	string s;

	ifstream in;

	in.open(arg);			// open 3rd input file
	while (getline(in,s)){
		list.push_back(s);
	}
	
	in.close();
	//sort(list.begin(), list.end(), greater<string>());
	return list;
}

double gpaVal2(string grade)
{
	if(grade == "C+")
		return 2.4;
	else if(grade == "C")
		return 2.0;
	else if(grade == "C-")
		return 1.7;
	else if(grade == "D+")
		return 1.4;
	else if(grade == "D")
		return 1.0;  
	else if(grade == "D-")
		return 0.7;
	else
		return 0.0;
}

double gpaVal(string grade)
{
	if(grade == "A")
		return 4.0;
	else if(grade == "A-")
		return 3.7;
	else if( grade == "B+")
		return 3.4;
	else if(grade == "B")
		return 3.0;
	else if(grade == "B-")
		return 2.7;
	else
		return gpaVal2(grade);
}

string findGpa(string students, vector<Grade> list)
{
	double gpa = 0.00;
	int count = 0;
	unsigned int fail = 0;
	stringstream s;

	for(unsigned int i = 0; i < list.size(); i++)
	{
		if(students == list[i].showId())
		{
			gpa += gpaVal(list[i].showGrade());
			count++;
		}
		else
			fail++;
	}
	if(fail == list.size())
		return "0.00";
	if(gpa > 0)
		gpa = gpa/count;
	s << setprecision(2) << fixed << gpa;

	return s.str();
}

vector<string> thirdMod(vector<Student> out1, vector<Grade> out2, vector<string> out3)
{
	vector<string> ret;

	for(unsigned int j = 0; j < out3.size(); j++)
	{
		ret.push_back(out3[j]);
		ret.push_back(findGpa(out3[j], out2));
		for (unsigned int i = 0; i < out1.size(); i++)
		{
			if(out1[i].showId() == out3[j])
			{
				ret.push_back(out1[i].showName());
				break;
			}
		}
	}


	return ret;
}

string display(vector<Grade> out2)
{
	stringstream output;
	for(unsigned int i = 0; i < out2.size(); i++) // make a class function that does this for me
	{
		output << out2[i].showId() << "    " << out2[i].showGrade() << "    " << out2[i].showClassId() 
						<< endl;
	}
	return output.str();
}

void is1st(vector<Student> &out1, vector<string> &out3)
{
	vector<int> ch;
	for(unsigned int i = 0; i < out3.size(); i++)
	{
		int yes = 0;
//		int y ;
		for(unsigned int j = 0; j < out1.size(); j++)
		{
			if(out3[i] == out1[j].showId())
			{
				yes++;
				break;
			}
		}
		if(yes == 0){
			ch.push_back(i);
		}
//			out3.erase(out3.begin()+y);
//		yes = 0;
	}
	sort(ch.begin(),ch.end());
	int gh = 0;
	for(unsigned int k = 0; k < ch.size(); k++)
	{
		out3.erase((out3.begin()+(ch[k]-gh)));
		gh++;
	}
}

int main(int argc, char* argv[])
{
	vector<Student> out1;
	vector<Grade> out2;
	vector<string> out3;
	vector<string> outf3;

	out1 = firstOut(argv[1]);

	
	out2 = secondOut(argv[2]);

	
	ofstream output;

	output.open(argv[4]);
	sort(out1.begin(),out1.end());
	if(out1[0].showName() != "0")
	{
		for(unsigned int i = 0; i < out1.size(); i++)
		{
			output << out1[i].showName() << endl << out1[i].showId() << endl << out1[i].showPhone() << endl << out1[i].showAdd() << endl;
		}
		output << endl;
	}

	out3 = thirdOut(argv[3]);
	is1st(out1,out3);
	outf3 = thirdMod(out1, out2, out3);
	//sortList(out2);
	sort(out2.begin(), out2.end());
	

	output << display(out2);
/*	for(unsigned int i = 0; i < out2.size(); i++) // make a class function that does this for me
	{
		output << out2[i].showId() << "    " << out2[i].showGrade() << "    " << out2[i].showClassId() 
						<< endl;
	}*/
	if(out1[0].showName() != "0")
	{
		output << endl;
		unsigned int u = 2;
		unsigned int o = 1;
		for(unsigned int i = 0; i < outf3.size(); i++)
		{
			if((outf3.size() > (i+o+1)))
			{
				if(outf3[(i+o)] == "a")
				{
					i+=2;
					continue;
				}		
			}
			output << outf3[i];
			if(i == u)
			{
				u+=3;
				output << endl;
			}
			else
				output << "    ";
		}
	}
	output.close();
	
	return 0;
}
