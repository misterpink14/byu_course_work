/************************************************

	Fixed mem leak issues (deconstructor)
	Sent appropriately 




*****************************************************/



#include "student.h"



// WORKSS **************************************
int SelectionSort(vector<Student> v)
{
	//if (v.size() > 2)
	//{
		int min;
		Student swap; //("","","","");
		for (int i = 0; i < v.size(); i++)
		{	
			min = i;
			for (int j = i + 1; j < v.size(); j++)
			{
				if (v[j] < v[min])
				{
					min = j;
					
				}
			}
			swap = v[i];
			v[i] = v[min];
			v[min] = swap;
		}
	//}
	/*else
	{
		int min = 0;
		for (int i = 0; i < v.size() - 1; i++)
		{
			if (v[i] < v[min])
			{
				min = i;
				
			}
		}
	}*/
	return v[0].count();
}
////********************************************************************8

//	
int InsertionSort(vector<Student> v)
{
	
	Student item;
//	v[0].resetCount();
	
	//if(v.size() < 3)
//		return v.size()/2;
	v[0].resetCount();
	for (int i = 1; i < v.size(); i++)
	{
		item = v[i];
		int j = i;
		while ((j>0) && (v[j - 1] > item))
		{
			v[j] = v[j - 1];
			j--;
		}
		v[j] = item;
	}

	return v[0].count();
}

//  fixxxx
int std_Sort(vector<Student> v)
{
	//cout << endl << v[0].count() << endl;
	sort(v.begin(), v.end());
	return v[0].count();
}

// fixxxx
int list_Sort(vector<Student> v)
{
	for (auto a : v)
	{
		cout << endl << a.showId();
	}
	cout << endl;
	list<Student> l;
	for (int i = 0; i < v.size(); i++)
	{
		l.push_back(v[i]);
	}
	
	l.sort();
	return v[0].count();
}


// ************************************************************


//
int LinearSearch(vector<Student> v, Student item)
{
	int count = 0;
	for (int i = 0; i < v.size(); i++)
	{
		count++;
		if (item == v[i])
		{
			break;
		}
	}
	return v[0].count();
}

// std::Find()
int std_Find(vector<Student> v, Student item)
{
	find(v.begin(), v.end(), item);
	return v[0].count();
}

// std::set.find()
int set_Find(vector<Student> v, Student item)
{
	set<Student> s;
	for (int i = 0; i < v.size(); i++)
	{
		s.insert(v[i]);
		v[0].resetCount();
	}
	v[0].resetCount();
	s.find(item);
	return v[0].count();
}
/////******************************************************



// open file		// DONEEE
void openStudentFile(string arg, vector<Student> &v)
{
	ifstream in;
	string id;
	string name;
	string number;
	string address;
	vector<string> comeon;
	string str;
	in.open(arg);
	
	while (getline(in, str))
		comeon.push_back(str);
	for (int i = 0; i < comeon.size(); i+=4)
	{	
		id = comeon[i];
		name = comeon[(i+1)];
		address = comeon[(i+2)];
		number = comeon[(i+3)];
		/*
		getline(in, id);
		getline(in, name);
		getline(in, address);
		getline(in, number);*/
		Student add(name, id, number, address);
		v.push_back(add);
	}
	in.close();
}


// DONE
void openQueryFile(string arg, vector<string> &q)
{
	ifstream in; 
	string str;

	in.open(arg);

	while (getline(in, str))
		q.push_back(str);

	in.close();
}
///*************************************************************



// DONEish
void sortFunction(vector<Student> &v, ofstream &out)
{
	stringstream out1;
	stringstream out2;
	stringstream out3;
	stringstream out4;
	out1 << "Selection Sort";
	out2 << "\nInsertion Sort";
	out3 << "\nstd::sort";
	out4 << "\nstd::list.sort";
	
	int size = v.size() / 4;
	for (int k = 0; k < 3; k++)
	{
		vector<Student> vec;
		for (int i = 0; i < size; i++)
			vec.push_back(v[i]);
		vec[0].resetCount();
		out1 << "\nsize: " << vec.size() << "    compares: " << SelectionSort(vec);//, size);
		vec[0].resetCount();
		out2 << "\nsize: " << vec.size() << "    compares: " << InsertionSort(vec);// , size);
		vec[0].resetCount();
		out3 << "\nsize: " << vec.size() << "    compares: " << std_Sort(vec);// , size);
		vec[0].resetCount();
		out4 << "\nsize: " << vec.size() << "    compares: " << list_Sort(vec);// , size);
		if (k == 0)
			size = v.size() / 2;
		else
			size = v.size();
	}
	out << out1.str() << out2.str() << out3.str() << out4.str();
}

//
void searchFunction(vector<Student> &v, vector<string> &q, ofstream &out)
{
	stringstream out1;
	stringstream out2;
	stringstream out3;
	stringstream out4;

	out1 << "\nLinear Search";
	out2 << "\nstd::find";
	out3 << "\nstd::set.find";
	
	int size0 = q.size() / 4;
	int size = v.size() / 4;
	for (int k = 0; k < 3; k++)
	{
		int avg1 = 0;
		int avg2 = 0;
		int avg3 = 0;

		vector<Student> vec;
		for (int i = 0; i < size; i++)
			vec.push_back(v[i]);
		for (int i = 0; i < size0; i++)
		{
			Student item("", q[i], "", "");
			v[0].resetCount();
			avg1 += LinearSearch(vec, item);
			v[0].resetCount(); 
			avg2 += std_Find(vec, item);
			v[0].resetCount(); 
			avg3 += set_Find(vec, item);
		}
		if(size0 != 0)
		{
			avg1 = (avg1) / (size0);
			avg2 = (avg2) / (size0);
			avg3 = (avg3) / (size0);
		}
		else
			avg1 = avg2 = avg3 = 0;
		out1 << "\nsize: " << size0 << "    compares: " << avg1;
		out2 << "\nsize: " << size0 << "    compares: " << avg2;
		out3 << "\nsize: " << size0 << "    compares: " << avg3;
		if (k == 0)
		{
			size = v.size() / 2;
			size0 = q.size() / 2;
		}
		else
		{
			size = v.size();
			size0 = q.size();
		}
	}
	out << out1.str() << out2.str() << out3.str();
}

/****************************
*  Main Function
*****************************/
int main(int argc, char *argv[])
{
	vector<Student> v;
	ofstream out;

	vector<string> q;
	
	// create vector
	openStudentFile(argv[1], v);

	// load the query
	openQueryFile(argv[2], q);

	out.open(argv[3]);
	sortFunction(v, out);
	searchFunction(v, q, out);
	out.close();
	system("pause");
}
