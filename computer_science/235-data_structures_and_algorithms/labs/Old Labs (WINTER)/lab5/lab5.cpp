#include "linkedlist.h"




using namespace std;





/*******************************************
*
*	Main Function
*
********************************************/
int main(int argc, char* argv[])
{
	string cmd;
	int index;
	string item;
	LinkedList<string> ll;// <string> ll;
	
	ifstream in;
	ofstream out;

	in.open(argv[1]);
	out.open(argv[2]);

	while (in >> cmd)
	{
		out << cmd;
		if (cmd == "insert")
		{
			in >> index;
			in >> item;
			out << " " << index << " " << item;
			ll.Insert(index, item);
			// insert index item
		}
		else if (cmd == "remove")
		{
			in >> index;
			out << " " << index << " " << ll.Remove(index);
		}
		else if (cmd == "find")
		{
			in >> item;
			out << " " << item << " " << ll.Find(item);
		}
		else if (cmd == "print")
		{
			ll.Print(out);  ///
		}
		else // (clear)
		{
			ll.Clear();
		}
		out << endl;
	}
	out.close();
	in.close();
}
