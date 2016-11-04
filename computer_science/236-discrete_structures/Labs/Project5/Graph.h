#ifndef GRAPH_H
#define GRAPH_H

#include "Node.h"

class Graph : public map <string, Node>
{
public:
	Graph() {}

	void output()
	{
		for (auto a: *this)
		{
			cout << a.first << " ";
			cout << a.second.PostOrder << " " << a.second.visited << endl;
		}
		cout << endl;
	}

};


#endif // GRAPH_H
