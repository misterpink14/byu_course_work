#ifndef NODE_H
#define NODE_H
#include <set>
#include <string>
#include <map>
using std::set;
using std::string;
using std::map;

class Node
{
public:
	set<string> NodeNames;
	string name;
	int PostOrder;
	bool visited;
	Node():PostOrder(0),visited(false) {}
};


#endif // NODE_H
