#ifndef TUPLE_H_
#define TUPLE_H_

#include<string>
#include<vector>
#include<iostream>

using std::vector;
using std::string;
using std::cout;
 
class Tuple : public vector < string >
{
public:
	Tuple() {};
//	Tuple(vector<string> &list) : Tuple(list){};

};

#endif